#include "apparatus.hpp"

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include <components/openmw-mp/Utils.hpp>
#include "../mwmp/Main.hpp"
#include "../mwmp/Networking.hpp"
/*
    End of tes3mp addition
*/

#include <components/esm/loadappa.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"

#include "../mwworld/ptr.hpp"
#include "../mwworld/actionalchemy.hpp"
#include "../mwworld/cellstore.hpp"
#include "../mwphysics/physicssystem.hpp"
#include "../mwworld/nullaction.hpp"

#include "../mwrender/objects.hpp"
#include "../mwrender/renderinginterface.hpp"

#include "../mwgui/tooltips.hpp"

namespace MWClass
{

    void Apparatus::insertObjectRendering (const MWWorld::Ptr& ptr, const std::string& model, MWRender::RenderingInterface& renderingInterface) const
    {
        if (!model.empty()) {
            renderingInterface.getObjects().insertModel(ptr, model);
        }
    }

    void Apparatus::insertObject(const MWWorld::Ptr& ptr, const std::string& model, osg::Quat rotation, MWPhysics::PhysicsSystem& physics, bool skipAnimated) const
    {
        // TODO: add option somewhere to enable collision for placeable objects

        /*
            Start of tes3mp addition

            Make it possible to enable collision for this object class from a packet
        */
        if (!model.empty())
        {
            mwmp::BaseWorldstate *worldstate = mwmp::Main::get().getNetworking()->getWorldstate();

            if (worldstate->hasPlacedObjectCollision || Utils::vectorContains(worldstate->enforcedCollisionRefIds, ptr.getCellRef().getRefId()))
            {
                if (worldstate->useActorCollisionForPlacedObjects)
                    physics.addObject(ptr, model, rotation, MWPhysics::CollisionType_Actor, skipAnimated);
                else
                    physics.addObject(ptr, model, rotation, MWPhysics::CollisionType_World, skipAnimated);
            }
        }
        /*
            End of tes3mp addition
        */
    }

    std::string Apparatus::getModel(const MWWorld::ConstPtr &ptr) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();

        const std::string &model = ref->mBase->mModel;
        if (!model.empty()) {
            return "meshes\\" + model;
        }
        return "";
    }

    std::string Apparatus::getName (const MWWorld::ConstPtr& ptr) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();
        const std::string& name = ref->mBase->mName;

        return !name.empty() ? name : ref->mBase->mId;
    }

    std::shared_ptr<MWWorld::Action> Apparatus::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor) const
    {
        return defaultItemActivate(ptr, actor);
    }

    std::string Apparatus::getScript (const MWWorld::ConstPtr& ptr) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();

        return ref->mBase->mScript;
    }

    int Apparatus::getValue (const MWWorld::ConstPtr& ptr) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();

        return ref->mBase->mData.mValue;
    }

    void Apparatus::registerSelf()
    {
        std::shared_ptr<Class> instance (new Apparatus);

        registerClass (typeid (ESM::Apparatus).name(), instance);
    }

    std::string Apparatus::getUpSoundId (const MWWorld::ConstPtr& ptr) const
    {
        return std::string("Item Apparatus Up");
    }

    std::string Apparatus::getDownSoundId (const MWWorld::ConstPtr& ptr) const
    {
        return std::string("Item Apparatus Down");
    }

    std::string Apparatus::getInventoryIcon (const MWWorld::ConstPtr& ptr) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();

        return ref->mBase->mIcon;
    }

    MWGui::ToolTipInfo Apparatus::getToolTipInfo (const MWWorld::ConstPtr& ptr, int count) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();

        MWGui::ToolTipInfo info;
        info.caption = MyGUI::TextIterator::toTagsString(getName(ptr)) + MWGui::ToolTips::getCountString(count);
        info.icon = ref->mBase->mIcon;

        std::string text;
        text += "\n#{sQuality}: " + MWGui::ToolTips::toString(ref->mBase->mData.mQuality);
        text += MWGui::ToolTips::getWeightString(ref->mBase->mData.mWeight, "#{sWeight}");
        text += MWGui::ToolTips::getValueString(ref->mBase->mData.mValue, "#{sValue}");

        if (MWBase::Environment::get().getWindowManager()->getFullHelp()) {
            text += MWGui::ToolTips::getCellRefString(ptr.getCellRef());
            text += MWGui::ToolTips::getMiscString(ref->mBase->mScript, "Script");
        }
        info.text = text;

        return info;
    }

    std::shared_ptr<MWWorld::Action> Apparatus::use (const MWWorld::Ptr& ptr, bool force) const
    {
        return std::shared_ptr<MWWorld::Action>(new MWWorld::ActionAlchemy(force));
    }

    MWWorld::Ptr Apparatus::copyToCellImpl(const MWWorld::ConstPtr &ptr, MWWorld::CellStore &cell) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();

        return MWWorld::Ptr(cell.insert(ref), &cell);
    }

    bool Apparatus::canSell (const MWWorld::ConstPtr& item, int npcServices) const
    {
        return (npcServices & ESM::NPC::Apparatus) != 0;
    }

    float Apparatus::getWeight(const MWWorld::ConstPtr &ptr) const
    {
        const MWWorld::LiveCellRef<ESM::Apparatus> *ref = ptr.get<ESM::Apparatus>();
        return ref->mBase->mData.mWeight;
    }
}
