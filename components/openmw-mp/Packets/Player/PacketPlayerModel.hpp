#ifndef OPENMW_PACKETPLAYERMODEL_HPP
#define OPENMW_PACKETPLAYERMODEL_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerModel : public PlayerPacket
    {
    public:
        PacketPlayerModel(RakNet::RakPeerInterface* peer);

        virtual void Packet(RakNet::BitStream* newBitstream, bool send);
    };
}

#endif
