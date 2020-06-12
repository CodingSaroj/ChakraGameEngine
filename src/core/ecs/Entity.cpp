#include "Entity.hpp"

Chakra::Entity::Entity(EntityID id)
    : m_ID(id), m_Enabled(true)
{
}

Chakra::EntityID Chakra::Entity::getID()
{
    return m_ID;
}

bool Chakra::Entity::isEnabled()
{
    return m_Enabled;
}

void Chakra::Entity::setEnabled(bool enabled)
{
    m_Enabled = enabled;
}
