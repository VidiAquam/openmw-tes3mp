#ifndef OPENMW_PACKETGMST_HPP
#define OPENMW_PACKETGMST_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

namespace mwmp
{
    class PacketGMST : public PlayerPacket
    {
    public:
        PacketGMST(RakNet::RakPeerInterface* peer);

        virtual void Packet(RakNet::BitStream* newBitstream, bool send);
    };
}

#endif //OPENMW_PACKETGMST_HPP
