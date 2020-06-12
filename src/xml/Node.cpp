#include "Node.hpp"

Chakra::XML::Node::Node(
                const std::string & name,
                const std::unordered_map<std::string, Attribute> & attributes,
                const std::string & data)
    : m_Name(name), m_Attributes(attributes), m_Data(data)
{
}

Chakra::XML::Node::Node(
                const std::string & name,
                const std::unordered_map<std::string, Attribute> & attributes,
                const std::unordered_map<std::string, Node> & children)
    : m_Name(name), m_Attributes(attributes), m_Children(children)
{
}

std::string Chakra::XML::Node::getName()
{
    return m_Name;
}

std::string Chakra::XML::Node::getAttributeValue(const std::string & name)
{
    return m_Attributes[name];
}

Node Chakra::XML::Node::getChild(const std::string & name)
{
    return m_Children[name];
}

std::string Chakra::XML::Node::getData()
{
    return m_Data;
}
