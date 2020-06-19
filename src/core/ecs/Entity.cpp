#include "Entity.hpp"

namespace Chakra
{
    Entity::Entity(EntityID id)
        : m_ID(id), m_Enabled(true)
    {
    }
    
    EntityID Entity::getID()
    {
        return m_ID;
    }
    
    bool Entity::isEnabled()
    {
        return m_Enabled;
    }
    
    void Entity::setEnabled(bool enabled)
    {
        m_Enabled = enabled;
    }
}
