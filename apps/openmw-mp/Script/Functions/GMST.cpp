#include "GMST.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/TimedLog.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>

void GMSTFunctions::SetGMST(unsigned short pid, const char* id, const char* GMSTvalue) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->gmsts[id] = GMSTvalue;
}

void GMSTFunctions::SendGMST(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket* packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GMST);
    packet->setPlayer(player);

    packet->Send(false);
}
