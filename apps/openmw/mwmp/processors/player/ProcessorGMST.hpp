#ifndef OPENMW_PROCESSORGMST_HPP
#define OPENMW_PROCESSORGMST_HPP

#include "apps/openmw/mwbase/environment.hpp"
#include "apps/openmw/mwworld/worldimp.hpp"
#include "apps/openmw/mwgui/windowmanagerimp.hpp"

#include "../PlayerProcessor.hpp"
#include <components/esm/variant.hpp>

namespace mwmp
{
    class ProcessorGMST final : public PlayerProcessor
    {
        
    public:
        ProcessorGMST()
        {
            BPP_INIT(ID_GMST)
        }

        virtual void Do(PlayerPacket& packet, BasePlayer* player)
        {
            LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_GMST from server");
            MWBase::World* world = MWBase::Environment::get().getWorld();
            for (std::pair<std::string, std::string> gmst : player->gmsts) {

                bool isGMST = world->getStore().get<ESM::GameSetting>().search(gmst.first);

                if (isGMST)
                {
                   const ESM::GameSetting baseGMST = *world->getStore().get<ESM::GameSetting>().search(gmst.first);
                   ESM::GameSetting finalGMST = baseGMST;
                   ESM::Variant baseValue = baseGMST.mValue;
                   ESM::Variant value = ESM::Variant(gmst.second);

                   switch (baseValue.getType()) {
                   case ESM::VarType::VT_Int :
                           try {
                               value = ESM::Variant(std::stoi(gmst.second));
                               value.setType(ESM::VarType::VT_Int);
                               
                           }
                           catch (std::invalid_argument) {
                               LOG_MESSAGE_SIMPLE(TimedLog::LOG_ERROR, "- Invalid value received for GMST %s (expected an integer, received a string)", gmst.first.c_str());
                           }
                           break;
                       case ESM::VarType::VT_Float :
                           try {
                               value = ESM::Variant(std::stof(gmst.second));
                               value.setType(ESM::VarType::VT_Float);
                               
                           }
                           catch (std::invalid_argument) {
                               LOG_MESSAGE_SIMPLE(TimedLog::LOG_ERROR, "- Invalid value received for GMST %s (expected a float, received a string)", gmst.first.c_str());
                           }
                           break;
                       default :
                           value.setType(ESM::VarType::VT_String);
                           break;
                   }

                   if (baseValue.getType() == value.getType())
                   {
                       finalGMST.mValue = value;
                       world->getModifiableStore().overrideRecord(finalGMST);
                       LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "- Setting GMST %s to %s", gmst.first.c_str(), gmst.second);
                   }

                }
                else
                {
                    player->gmsts[gmst.first].clear();
                    LOG_MESSAGE_SIMPLE(TimedLog::LOG_ERROR, "- Received packet for nonexistant GMST %s", gmst.first.c_str());
                }

                
            }

            
            
        }
    };
}

#endif //OPENMW_PROCESSORGMST_HPP
