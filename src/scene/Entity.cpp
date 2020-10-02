#include "Entity.hpp"

namespace Chakra
{
    Entity::Entity(entt::entity handle, entt::registry * registry)
        : m_Handle(handle), m_Registry(registry)
    {
    }
}
