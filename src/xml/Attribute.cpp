#include "Attribute.hpp"

namespace Chakra
{
    namespace XML
    {
        Attribute::Attribute(const std::string & value)
            : m_Value(value)
        {
        }
        
        std::string Attribute::getValue()
        {
            return m_Value;
        }
    }
}
