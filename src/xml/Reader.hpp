#ifndef CHAKRA_XML_READER_HPP
#define CHAKRA_XML_READER_HPP

#include <libxml2/xmlReader.h>

#include "xml/Node.hpp"

namespace Chakra
{
    namespace XML
    {
        class Reader
        {
            public:
                Node(const std::string & rawData);

                Node getRootNode();

            private:
                Node m_Root;
        };
    }
}

#endif
