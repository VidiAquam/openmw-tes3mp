#ifndef OPENMW_MODELAPI_HPP
#define OPENMW_MODELAPI_HPP

#include "../Types.hpp"

#define MODELAPI \
    {"SetModel",               ModelFunctions::SetModel},\
    {"ResetModel",             ModelFunctions::ResetModel},\
    \
    {"SendModel",              ModelFunctions::SendModel}

class ModelFunctions
{
public:

    /**
    * \brief Set the model of a player.
    *
    * This changes the model recorded for that player in the server memory, but
    * does not by itself send a packet.
    *
    * \param pid The player ID.
    * \param model The new model (e.g. "base_anim.nif").
    * \return void
    */
    static void SetModel(unsigned short pid, const char* model) noexcept;

    /**
    * \brief Reset the model of a player to its original value.
    *
    * This changes the model recorded for that player in the server memory, but
    * does not by itself send a packet.
    *
    * \param pid The player ID.
    * \return void
    */
    static void ResetModel(unsigned short pid) noexcept;


    /**
    * \brief Send a PlayerModel packet about a player.
    *
    * This sends the packet to all players connected to the server. 
    *
    * \param pid The player ID.
    * \return void
    */
    static void SendModel(unsigned short pid);
};

#endif //OPENMW_MODELAPI_HPP
