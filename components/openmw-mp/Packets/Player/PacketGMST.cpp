#include "PacketGMST.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketGMST::PacketGMST(RakNet::RakPeerInterface* peer) : PlayerPacket(peer)
{
    packetID = ID_GMST;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketGMST::Packet(RakNet::BitStream* newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    uint32_t gmstCount = static_cast<uint32_t>(player->gmsts.size());
    RW(gmstCount, send);

    std::string mapIndex;
    std::string mapValue;

    if (send)
    {
        for (auto&& gmst : player->gmsts)
        {
            mapIndex = gmst.first;
            mapValue = gmst.second;
            RW(mapIndex, send, false);
            RW(mapValue, send, false);
        }
        player->gmsts.clear();
    }
    else
    {
        player->gmsts.clear();
        for (unsigned int n = 0; n < gmstCount; n++)
        {
            RW(mapIndex, send, false);
            RW(mapValue, send, false);
            player->gmsts[mapIndex] = mapValue;
        }
    }
}
