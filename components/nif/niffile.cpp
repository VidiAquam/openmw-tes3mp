#include "niffile.hpp"
#include "effect.hpp"

#include <map>
#include <sstream>

namespace Nif
{

/// Open a NIF stream. The name is used for error messages.
NIFFile::NIFFile(Files::IStreamPtr stream, const std::string &name)
    : filename(name)
{
    parse(stream);
}

NIFFile::~NIFFile()
{
    for (Record* record : records)
        delete record;
}

template <typename NodeType> static Record* construct() { return new NodeType; }

struct RecordFactoryEntry {

    using create_t = Record* (*)();

    create_t        mCreate;
    RecordType      mType;

};

///These are all the record types we know how to read.
static std::map<std::string,RecordFactoryEntry> makeFactory()
{
    std::map<std::string,RecordFactoryEntry> factory;
    factory["NiNode"]                       = {&construct <NiNode>                      , RC_NiNode                     };
    factory["NiSwitchNode"]                 = {&construct <NiSwitchNode>                , RC_NiSwitchNode               };
    factory["NiLODNode"]                    = {&construct <NiLODNode>                   , RC_NiLODNode                  };
    factory["AvoidNode"]                    = {&construct <NiNode>                      , RC_AvoidNode                  };
    factory["NiCollisionSwitch"]            = {&construct <NiNode>                      , RC_NiCollisionSwitch          };
    factory["NiBSParticleNode"]             = {&construct <NiNode>                      , RC_NiBSParticleNode           };
    factory["NiBSAnimationNode"]            = {&construct <NiNode>                      , RC_NiBSAnimationNode          };
    factory["NiBillboardNode"]              = {&construct <NiNode>                      , RC_NiBillboardNode            };
    factory["NiTriShape"]                   = {&construct <NiTriShape>                  , RC_NiTriShape                 };
    factory["NiTriStrips"]                  = {&construct <NiTriStrips>                 , RC_NiTriStrips                };
    factory["NiLines"]                      = {&construct <NiLines>                     , RC_NiLines                    };
    factory["NiRotatingParticles"]          = {&construct <NiRotatingParticles>         , RC_NiRotatingParticles        };
    factory["NiAutoNormalParticles"]        = {&construct <NiAutoNormalParticles>       , RC_NiAutoNormalParticles      };
    factory["NiCamera"]                     = {&construct <NiCamera>                    , RC_NiCamera                   };
    factory["RootCollisionNode"]            = {&construct <NiNode>                      , RC_RootCollisionNode          };
    factory["NiTexturingProperty"]          = {&construct <NiTexturingProperty>         , RC_NiTexturingProperty        };
    factory["NiFogProperty"]                = {&construct <NiFogProperty>               , RC_NiFogProperty              };
    factory["NiMaterialProperty"]           = {&construct <NiMaterialProperty>          , RC_NiMaterialProperty         };
    factory["NiZBufferProperty"]            = {&construct <NiZBufferProperty>           , RC_NiZBufferProperty          };
    factory["NiAlphaProperty"]              = {&construct <NiAlphaProperty>             , RC_NiAlphaProperty            };
    factory["NiVertexColorProperty"]        = {&construct <NiVertexColorProperty>       , RC_NiVertexColorProperty      };
    factory["NiShadeProperty"]              = {&construct <NiShadeProperty>             , RC_NiShadeProperty            };
    factory["NiDitherProperty"]             = {&construct <NiDitherProperty>            , RC_NiDitherProperty           };
    factory["NiWireframeProperty"]          = {&construct <NiWireframeProperty>         , RC_NiWireframeProperty        };
    factory["NiSpecularProperty"]           = {&construct <NiSpecularProperty>          , RC_NiSpecularProperty         };
    factory["NiStencilProperty"]            = {&construct <NiStencilProperty>           , RC_NiStencilProperty          };
    factory["NiVisController"]              = {&construct <NiVisController>             , RC_NiVisController            };
    factory["NiGeomMorpherController"]      = {&construct <NiGeomMorpherController>     , RC_NiGeomMorpherController    };
    factory["NiKeyframeController"]         = {&construct <NiKeyframeController>        , RC_NiKeyframeController       };
    factory["NiAlphaController"]            = {&construct <NiAlphaController>           , RC_NiAlphaController          };
    factory["NiRollController"]             = {&construct <NiRollController>            , RC_NiRollController           };
    factory["NiUVController"]               = {&construct <NiUVController>              , RC_NiUVController             };
    factory["NiPathController"]             = {&construct <NiPathController>            , RC_NiPathController           };
    factory["NiMaterialColorController"]    = {&construct <NiMaterialColorController>   , RC_NiMaterialColorController  };
    factory["NiBSPArrayController"]         = {&construct <NiBSPArrayController>        , RC_NiBSPArrayController       };
    factory["NiParticleSystemController"]   = {&construct <NiParticleSystemController>  , RC_NiParticleSystemController };
    factory["NiFlipController"]             = {&construct <NiFlipController>            , RC_NiFlipController           };
    factory["NiAmbientLight"]               = {&construct <NiLight>                     , RC_NiLight                    };
    factory["NiDirectionalLight"]           = {&construct <NiLight>                     , RC_NiLight                    };
    factory["NiPointLight"]                 = {&construct <NiPointLight>                , RC_NiLight                    };
    factory["NiSpotLight"]                  = {&construct <NiSpotLight>                 , RC_NiLight                    };
    factory["NiTextureEffect"]              = {&construct <NiTextureEffect>             , RC_NiTextureEffect            };
    factory["NiVertWeightsExtraData"]       = {&construct <NiVertWeightsExtraData>      , RC_NiVertWeightsExtraData     };
    factory["NiTextKeyExtraData"]           = {&construct <NiTextKeyExtraData>          , RC_NiTextKeyExtraData         };
    factory["NiStringExtraData"]            = {&construct <NiStringExtraData>           , RC_NiStringExtraData          };
    factory["NiGravity"]                    = {&construct <NiGravity>                   , RC_NiGravity                  };
    factory["NiPlanarCollider"]             = {&construct <NiPlanarCollider>            , RC_NiPlanarCollider           };
    factory["NiSphericalCollider"]          = {&construct <NiSphericalCollider>         , RC_NiSphericalCollider        };
    factory["NiParticleGrowFade"]           = {&construct <NiParticleGrowFade>          , RC_NiParticleGrowFade         };
    factory["NiParticleColorModifier"]      = {&construct <NiParticleColorModifier>     , RC_NiParticleColorModifier    };
    factory["NiParticleRotation"]           = {&construct <NiParticleRotation>          , RC_NiParticleRotation         };
    factory["NiFloatData"]                  = {&construct <NiFloatData>                 , RC_NiFloatData                };
    factory["NiTriShapeData"]               = {&construct <NiTriShapeData>              , RC_NiTriShapeData             };
    factory["NiTriStripsData"]              = {&construct <NiTriStripsData>             , RC_NiTriStripsData            };
    factory["NiLinesData"]                  = {&construct <NiLinesData>                 , RC_NiLinesData                };
    factory["NiVisData"]                    = {&construct <NiVisData>                   , RC_NiVisData                  };
    factory["NiColorData"]                  = {&construct <NiColorData>                 , RC_NiColorData                };
    factory["NiPixelData"]                  = {&construct <NiPixelData>                 , RC_NiPixelData                };
    factory["NiMorphData"]                  = {&construct <NiMorphData>                 , RC_NiMorphData                };
    factory["NiKeyframeData"]               = {&construct <NiKeyframeData>              , RC_NiKeyframeData             };
    factory["NiSkinData"]                   = {&construct <NiSkinData>                  , RC_NiSkinData                 };
    factory["NiUVData"]                     = {&construct <NiUVData>                    , RC_NiUVData                   };
    factory["NiPosData"]                    = {&construct <NiPosData>                   , RC_NiPosData                  };
    factory["NiRotatingParticlesData"]      = {&construct <NiRotatingParticlesData>     , RC_NiRotatingParticlesData    };
    factory["NiAutoNormalParticlesData"]    = {&construct <NiAutoNormalParticlesData>   , RC_NiAutoNormalParticlesData  };
    factory["NiSequenceStreamHelper"]       = {&construct <NiSequenceStreamHelper>      , RC_NiSequenceStreamHelper     };
    factory["NiSourceTexture"]              = {&construct <NiSourceTexture>             , RC_NiSourceTexture            };
    factory["NiSkinInstance"]               = {&construct <NiSkinInstance>              , RC_NiSkinInstance             };
    factory["NiLookAtController"]           = {&construct <NiLookAtController>          , RC_NiLookAtController         };
    factory["NiPalette"]                    = {&construct <NiPalette>                   , RC_NiPalette                  };
    return factory;
}


///Make the factory map used for parsing the file
static const std::map<std::string,RecordFactoryEntry> factories = makeFactory();

std::string NIFFile::printVersion(unsigned int version)
{
    int major = (version >> 24) & 0xFF;
    int minor = (version >> 16) & 0xFF;
    int patch = (version >> 8) & 0xFF;
    int rev = version & 0xFF;

    std::stringstream stream;
    stream << major << "." << minor << "." << patch << "." << rev;
    return stream.str();
}

void NIFFile::parse(Files::IStreamPtr stream)
{
    NIFStream nif (this, stream);

    // Check the header string
    std::string head = nif.getVersionString();
    if(head.compare(0, 22, "NetImmerse File Format") != 0)
        fail("Invalid NIF header: " + head);

    // Get BCD version
    ver = nif.getUInt();
    // 4.0.0.0 is an older, practically identical version of the format.
    // It's not used by Morrowind assets but Morrowind supports it.
    if(ver != NIFStream::generateVersion(4,0,0,0) && ver != VER_MW)
        fail("Unsupported NIF version: " + printVersion(ver));
    // Number of records
    size_t recNum = nif.getUInt();
    records.resize(recNum);

    for(size_t i = 0;i < recNum;i++)
    {
        Record *r = nullptr;

        std::string rec = nif.getString();
        if(rec.empty())
        {
            std::stringstream error;
            error << "Record number " << i << " out of " << recNum << " is blank.";
            fail(error.str());
        }

        std::map<std::string,RecordFactoryEntry>::const_iterator entry = factories.find(rec);

        if (entry != factories.end())
        {
            r = entry->second.mCreate ();
            r->recType = entry->second.mType;
        }
        else
            fail("Unknown record type " + rec);

        assert(r != nullptr);
        assert(r->recType != RC_MISSING);
        r->recName = rec;
        r->recIndex = i;
        records[i] = r;
        r->read(&nif);
    }

    size_t rootNum = nif.getUInt();
    roots.resize(rootNum);

    //Determine which records are roots
    for(size_t i = 0;i < rootNum;i++)
    {
        int idx = nif.getInt();
        if (idx >= 0 && idx < int(records.size()))
        {
            roots[i] = records[idx];
        }
        else
        {
            roots[i] = nullptr;
            warn("Null Root found");
        }
    }

    // Once parsing is done, do post-processing.
    for (Record* record : records)
        record->post(this);
}

void NIFFile::setUseSkinning(bool skinning)
{
    mUseSkinning = skinning;
}

bool NIFFile::getUseSkinning() const
{
    return mUseSkinning;
}

}
