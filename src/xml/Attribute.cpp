#include "Attribute.hpp"

Chakra::XML::Attribute::XMLAttribute(const std::string & value)
    : m_Value(value)
{
}

std::string getValue()
{
    return m_Value;
}
