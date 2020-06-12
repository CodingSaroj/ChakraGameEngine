#ifndef CHAKRA_XML_NODE_HPP
#define CHAKRA_XML_NODE_HPP

#include <unordered_map>
#include <vector>

#include "xml/Attribute.hpp"

namespace Chakra
{
    namespace XML
    {
        class Node
        {
            public:
                Node(const std::string & name,
                     const std::unordered_map<std::string, Attribute> & attributes,
                     const std::string & data);

                Node(const std::string & name,
                     const std::unordered_map<std::string, Attribute> & attributes,
                     const std::unordered_map<std::string, Node> & children);

                std::string getName();
                std::string getAttributeValue(const std::string & name);
                Node        getChild(const std::string & name);
                std::string getData();

            private:
                const std::string                          m_Name;
                std::unordered_map<std::string, Attribute> m_Attributes;
                std::unordered_map<std::string, Node>      m_Children;
                const std::string                          m_Data;
        };
    }
}

#endif
