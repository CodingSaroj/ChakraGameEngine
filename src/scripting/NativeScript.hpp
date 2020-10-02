#ifndef CHAKRA_SCRIPTING_NATIVE_SCRIPT_HPP
#define CHAKRA_SCRIPTING_NATIVE_SCRIPT_HPP

#include "scene/Entity.hpp"

namespace Chakra
{
    namespace Scripting
    {
        class NativeScript
        {
        protected:
            template <typename T, typename... CArgs>
            T & AddComponent(CArgs... cargs)
            {
                return m_EntityHandle.AddComponent<T>(std::forward<CArgs>(cargs)...);
            }

            template <typename T>
            T & GetComponent()
            {
                return m_EntityHandle.GetComponent<T>();
            }
            
            template <typename T>
            void RemoveComponent()
            {
                return m_EntityHandle.RemoveComponent<T>();
            }

        public:
            void SetEntity(Entity handle) { m_EntityHandle = handle; }

            virtual void OnCreate() {} 
            virtual void OnUpdate() {}

        private:
            Entity m_EntityHandle;
        };
    }
}

#endif
