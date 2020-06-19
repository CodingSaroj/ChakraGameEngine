#include "Assets.hpp"

namespace Chakra
{
    BinaryData::BinaryData(const std::string & data)
        : Asset(AssetMetaType::BinaryData), m_Data(data)
    {
    }
    
    std::string BinaryData::getData()
    {
        return m_Data;
    }
    
    TextData::TextData(const std::string & data)
        : Asset(AssetMetaType::TextData), m_Data(data)
    {
    }
    
    std::string TextData::getData()
    {
        return m_Data;
    }
    
    XMLTree::XMLTree(const XML::Node & root)
        : Asset(AssetMetaType::XMLTree), m_Root(root)
    {
    }
    
    XML::Node XMLTree::getRoot()
    {
        return m_Root;
    }
}
