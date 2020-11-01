#ifndef GAME_MWMECHANICS_AIACTIVATE_H
#define GAME_MWMECHANICS_AIACTIVATE_H

#include "typedaipackage.hpp"

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include "../mwworld/ptr.hpp"
/*
    End of tes3mp addition
*/

#include <string>

#include "pathfinding.hpp"

namespace ESM
{
namespace AiSequence
{
    struct AiActivate;
}
}

namespace MWMechanics
{
    /// \brief Causes actor to walk to activatable object and activate it
    /** Will activate when close to object **/
    class AiActivate final : public TypedAiPackage<AiActivate>
    {
        public:
            /// Constructor
            /** \param objectId Reference to object to activate **/
            explicit AiActivate(const std::string &objectId);

            /*
                Start of tes3mp addition

                Make it possible to initialize an AiActivate package with a specific Ptr
                as the target, allowing for more fine-tuned activation of objects
            */
            explicit AiActivate(MWWorld::Ptr object);
            /*
                End of tes3mp addition
            */

            explicit AiActivate(const ESM::AiSequence::AiActivate* activate);

            bool execute (const MWWorld::Ptr& actor, CharacterController& characterController, AiState& state, float duration) override;

            static constexpr AiPackageTypeId getTypeId() { return AiPackageTypeId::Activate; }

            void writeState(ESM::AiSequence::AiSequence& sequence) const override;

        private:
            const std::string mObjectId;

            /*
                Start of tes3mp addition

                Track the object associated with this AiActivate package
            */
            MWWorld::Ptr mObjectPtr;
            /*
                End of tes3mp addition
            */
    };
}
#endif // GAME_MWMECHANICS_AIACTIVATE_H
