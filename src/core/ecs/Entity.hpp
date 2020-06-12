#ifndef CHAKRA_ENTITY_HPP
#define CHAKRA_ENTITY_HPP

#include "core/ecs/ComponentManager.hpp"

namespace Chakra
{
    class Entity
    {
        public:
            Entity(EntityID id);

            EntityID getID();
            bool     isEnabled();
            void     setEnabled(bool enabled);

            template <typename T>
            void addComponent(const T & component)
            {
                ComponentManager<T>::Register(m_ID, component);
            }

            template <typename T>
            T & getComponent()
            {
                return ComponentManager<T>::Get(m_ID);
            }

            template <typename T>
            void removeComponent()
            {
                ComponentManager<T>::Remove(m_ID);
            }

        private:
            EntityID    m_ID;
            bool        m_Enabled;
    };
}

#endif
