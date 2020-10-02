#ifndef CHAKRA_SCENE_ENTITY_HPP
#define CHAKRA_SCENE_ENTITY_HPP

#include "core/Common.hpp"

#include "core/Logger.hpp"

#include <entt/entt.hpp>

namespace Chakra
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, entt::registry * registry);

        constexpr bool IsValid()
        {
            return m_Registry != nullptr && m_Handle != entt::null;
        }

        template <typename ComponentType, typename... ComponentArgs>
        ComponentType & AddComponent(ComponentArgs... cargs)
        {
            CHK_ASSERT(IsValid(), "Scene::Entity::AddComponent", "Invalid instance.")

            if (m_Registry->has<ComponentType>(m_Handle))
            {
                CHK_WARNING("Scene::Entity::AddComponent", "Component ", typeid(ComponentType).name(), " already exists.");

                return m_Registry->get<ComponentType>(m_Handle);
            }
            else
            {
                return m_Registry->emplace<ComponentType>(m_Handle, std::forward<ComponentArgs>(cargs)...);
            }
        }
        
        template <typename ComponentType>
        bool HasComponent()
        {
            CHK_ASSERT(IsValid(), "Scene::Entity::HasComponent", "Invalid instance.")

            return m_Registry->has<ComponentType>(m_Handle);
        }
        
        template <typename ComponentType>
        ComponentType & GetComponent()
        {
            CHK_ASSERT(IsValid(), "Scene::Entity::GetComponent", "Invalid instance.")

            CHK_ASSERT(HasComponent<ComponentType>(), "Scene::Entity::GetComponent", "Entity ", (uint32_t)m_Handle, " doesn't have component ", typeid(ComponentType).name(), ".")

            return m_Registry->get<ComponentType>(m_Handle);
        }

        template <typename ComponentType>
        void RemoveComponent()
        {
            CHK_ASSERT(IsValid(), "Scene::Entity::RemoveComponent", "Invalid instance.")

            CHK_ASSERT(m_Registry->has<ComponentType>(m_Handle), "Scene::Entity::RemoveComponent", "Entity ", (uint32_t)m_Handle, " doesn't have component ", typeid(ComponentType).name(), ".");

            m_Registry->remove<ComponentType>(m_Handle);
        }

    private:
        entt::registry * m_Registry = nullptr;
        entt::entity     m_Handle = entt::null;

        friend class Scene;
    };
}

#endif
