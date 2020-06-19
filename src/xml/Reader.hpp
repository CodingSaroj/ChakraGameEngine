#ifndef CHAKRA_XML_READER_HPP
#define CHAKRA_XML_READER_HPP

#include "core/Common.hpp"

#include <libxml/xmlreader.h>

#include "core/Logger.hpp"

#include "xml/Node.hpp"

namespace Chakra
{
    namespace XML
    {
        class Reader
        {
            public:
                Reader(const std::string & rawData);

                Node getRootNode();

            private:
                Node * m_Root;

                void processNode(Node ** target, xmlNodePtr node);
        };
    }
}

#endif
