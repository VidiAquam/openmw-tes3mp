#ifndef OPENMW_GMSTAPI_HPP
#define OPENMW_GMSTAPI_HPP

#include "../Types.hpp"

#define GMSTAPI \
    {"SetGMST",               GMSTFunctions::SetGMST},\
    \
    {"SendGMST",              GMSTFunctions::SendGMST}

class GMSTFunctions
{
public:

    /**
    * \brief Set a GMST game setting for a player.
    *
    * This changes the GMST recorded for that player in the server memory, but
    * does not by itself send a packet.
    *
    * \param pid The player ID.
    * \param id The name of the GMST setting.
    * \param value The value of the GMST.
    * \return void
    */
    static void SetGMST(unsigned short pid, const char* id, const char* GMSTvalue) noexcept;

    /**
    * \brief Send a GMST packet to the player affected by it.
    *
    * \param pid The player ID to send it to.
    * \return void
    */
    static void SendGMST(unsigned short pid) noexcept;
};

#endif //OPENMW_GMSTAPI_HPP
