#ifndef OPENMW_BASEEVENT_HPP
#define OPENMW_BASEEVENT_HPP

#include <components/esm/loadcell.hpp>
#include <components/openmw-mp/Base/BaseStructs.hpp>
#include <RakNetTypes.h>

namespace mwmp
{
    struct ContainerItem
    {
        std::string refId;
        int count;
        int charge;
        double enchantmentCharge;
        std::string soul;

        int actionCount;

        inline bool operator==(const ContainerItem& rhs)
        {
            return refId == rhs.refId && count == rhs.count && charge == rhs.charge &&
                enchantmentCharge == rhs.enchantmentCharge && soul == rhs.soul;
        }
    };

    struct BaseObject
    {
        std::string refId;
        unsigned int refNum;
        unsigned int mpNum;
        int count;
        int charge;
        double enchantmentCharge;
        std::string soul;
        int goldValue;

        ESM::Position position;

        bool objectState;
        int lockLevel;
        float scale;

        std::string soundId;
        float volume;
        float pitch;

        unsigned int goldPool;
        float lastGoldRestockHour;
        int lastGoldRestockDay;


        int doorState;
        bool teleportState;
        ESM::Cell destinationCell;
        ESM::Position destinationPosition;

        std::string musicFilename;

        std::string videoFilename;
        bool allowSkipping;

        std::string animGroup;
        int animMode;

        bool isDisarmed;
        bool droppedByPlayer;

        Target activatingActor;
        Target hittingActor;
        Attack hitAttack;

        bool isSummon;
        int summonEffectId;
        std::string summonSpellId;
        int summonEffectIndex;
        float summonDuration;
        Target master;

        bool hasContainer;

        std::vector<ClientVariable> clientLocals;
        std::vector<ContainerItem> containerItems;
        unsigned int containerItemCount;

        RakNet::RakNetGUID guid; // only for object lists that can also include players
        bool isPlayer;
    };

    class BaseObjectList
    {
    public:

        BaseObjectList(RakNet::RakNetGUID guid) : guid(guid)
        {

        }

        BaseObjectList()
        {

        }

        enum WORLD_ACTION
        {
            SET = 0,
            ADD = 1,
            REMOVE = 2,
            REQUEST = 3
        };

        enum CONTAINER_SUBACTION
        {
            NONE = 0,
            DRAG = 1,
            DROP = 2,
            TAKE_ALL = 3,
            REPLY_TO_REQUEST = 4,
            TRADE = 6
        };

        RakNet::RakNetGUID guid;
        
        std::vector<BaseObject> baseObjects;
        unsigned int baseObjectCount;

        ESM::Cell cell;
        std::string consoleCommand;

        unsigned char packetOrigin; // 0 - Gameplay, 1 - Console, 2 - Client script, 3 - Server script
        std::string originClientScript;

        unsigned char action; // 0 - Clear and set in entirety, 1 - Add item, 2 - Remove item, 3 - Request items
        unsigned char containerSubAction; // 0 - None, 1 - Drag, 2 - Drop, 3 - Take all, 4 - Reply to request

        bool isValid;
    };
}

#endif //OPENMW_BASEEVENT_HPP
