#include "PacketPlayerModel.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerModel::PacketPlayerModel(RakNet::RakPeerInterface* peer) : PlayerPacket(peer) {
    //set packet ID
    packetID = ID_PLAYER_MODEL;
    priority = MEDIUM_PRIORITY;
}


void PacketPlayerModel::Packet(RakNet::BitStream* newBitstream, bool send) {
    PlayerPacket::Packet(newBitstream, send);
    RW(player->model, send);
}
