#ifndef GAME_MWCLASS_CONTAINER_H
#define GAME_MWCLASS_CONTAINER_H

#include "../mwworld/class.hpp"
#include "../mwworld/containerstore.hpp"
#include "../mwworld/customdata.hpp"

namespace ESM
{
    struct Container;
    struct InventoryState;
}

namespace MWClass
{
    class ContainerCustomData : public MWWorld::CustomData
    {
        MWWorld::ContainerStore mStore;
    public:
        ContainerCustomData(const ESM::Container& container, MWWorld::CellStore* cell);
        ContainerCustomData(const ESM::InventoryState& inventory);

        virtual MWWorld::CustomData *clone() const;

        virtual ContainerCustomData& asContainerCustomData();
        virtual const ContainerCustomData& asContainerCustomData() const;

        friend class Container;
    };

    class Container : public MWWorld::Class
    {
            void ensureCustomData (const MWWorld::Ptr& ptr) const;


            virtual MWWorld::Ptr copyToCellImpl(const MWWorld::ConstPtr &ptr, MWWorld::CellStore &cell) const;

        public:

            virtual void insertObjectRendering (const MWWorld::Ptr& ptr, const std::string& model, MWRender::RenderingInterface& renderingInterface) const;
            ///< Add reference into a cell for rendering

            virtual void insertObject(const MWWorld::Ptr& ptr, const std::string& model, MWPhysics::PhysicsSystem& physics) const;

            virtual std::string getName (const MWWorld::ConstPtr& ptr) const;
            ///< \return name or ID; can return an empty string.

            virtual std::shared_ptr<MWWorld::Action> activate (const MWWorld::Ptr& ptr,
                const MWWorld::Ptr& actor) const;
            ///< Generate action for activation

            virtual bool hasToolTip (const MWWorld::ConstPtr& ptr) const;
            ///< @return true if this object has a tooltip when focused (default implementation: true)

            virtual MWGui::ToolTipInfo getToolTipInfo (const MWWorld::ConstPtr& ptr, int count) const;
            ///< @return the content of the tool tip to be displayed. raises exception if the object has no tooltip.

            virtual MWWorld::ContainerStore& getContainerStore (const MWWorld::Ptr& ptr) const;
            ///< Return container store

            /*
                Start of tes3mp addition

                Make it possible to check whether a class has a container store
            */
            virtual bool hasContainerStore(const MWWorld::Ptr &ptr) const { return true; }
            /*
                End of tes3mp addition
            */

            virtual std::string getScript (const MWWorld::ConstPtr& ptr) const;
            ///< Return name of the script attached to ptr

            virtual float getCapacity (const MWWorld::Ptr& ptr) const;
            ///< Return total weight that fits into the object. Throws an exception, if the object can't
            /// hold other objects.

            virtual float getEncumbrance (const MWWorld::Ptr& ptr) const;
            ///< Returns total weight of objects inside this object (including modifications from magic
            /// effects). Throws an exception, if the object can't hold other objects.

            virtual bool canLock(const MWWorld::ConstPtr &ptr) const;

            virtual void readAdditionalState (const MWWorld::Ptr& ptr, const ESM::ObjectState& state)
                const;
            ///< Read additional state from \a state into \a ptr.

            virtual void writeAdditionalState (const MWWorld::ConstPtr& ptr, ESM::ObjectState& state)
                const;
            ///< Write additional state from \a ptr into \a state.

            static void registerSelf();

            virtual void respawn (const MWWorld::Ptr& ptr) const;

            virtual std::string getModel(const MWWorld::ConstPtr &ptr) const;

            virtual bool useAnim() const;
    };
}

#endif
