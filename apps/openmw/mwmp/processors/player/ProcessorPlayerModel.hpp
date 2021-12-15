#ifndef OPENMW_PROCESSORPLAYERMODEL_HPP
#define OPENMW_PROCESSORPLAYERMODEL_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerModel final : public PlayerProcessor
    {
    public:
        ProcessorPlayerModel()
        {
            BPP_INIT(ID_PLAYER_MODEL)
        }

        virtual void Do(PlayerPacket& packet, BasePlayer* player)
        {
            LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_PLAYER_MODEL from server");

            if (isLocal())
            {
                LOG_APPEND(TimedLog::LOG_INFO, "- Packet was about LocalPlayer");

                static_cast<LocalPlayer*>(player)->setModel();
            }
            else if (player != 0)
            {
                static_cast<DedicatedPlayer*>(player)->setModel();
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERMODEL_HPP