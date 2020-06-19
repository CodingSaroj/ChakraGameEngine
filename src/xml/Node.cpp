#include "Node.hpp"

namespace Chakra
{
    namespace XML
    {
        Node::Node(
                        const std::string & name,
                        const std::unordered_map<std::string, Attribute> & attributes,
                        const std::string & data,
                        const std::unordered_map<std::string, Node *> & children)
            : m_Name(name), m_Attributes(attributes), m_Data(data), m_Children(children)
        {
        }
        
        std::string Node::getName()
        {
            return m_Name;
        }
        
        std::string Node::getAttributeValue(const std::string & name)
        {
            return m_Attributes[name].getValue();
        }
        
        Node && Node::getChild(const std::string & name)
        {
            return std::move(*m_Children[name]);
        }
        
        std::string Node::getData()
        {
            return m_Data;
        }
    }
}
