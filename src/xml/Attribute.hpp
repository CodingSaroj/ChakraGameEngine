#ifndef CHAKRA_XML_ATTRIBUTE_HPP
#define CHAKRA_XML_ATTRIBUTE_HPP

#include <string>

namespace Chakra
{
    namespace XML
    {
        class Attribute
        {
            public:
                Attribute(const std::string & value);

                std::string getValue();

            private:
                const std::string m_Value;
        };
    }
}

#endif
