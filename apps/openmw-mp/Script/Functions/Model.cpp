#include "Model.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/TimedLog.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

void ModelFunctions::SetModel(unsigned short pid, const char* model) noexcept
{
    Player* player;
    GET_PLAYER(pid, player, );

    player->model = model;
}

void ModelFunctions::SendModel(unsigned short pid)
{
    Player* player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket* packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_MODEL);
    packet->setPlayer(player);

    packet->Send(false);
    packet->Send(true);
}
