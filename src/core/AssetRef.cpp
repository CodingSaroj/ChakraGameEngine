#include "AssetRef.hpp"

namespace Chakra
{
    AssetRef::AssetRef(const std::string & key)
        : m_Key(key)
    {
    }
    
    Asset * AssetRef::follow()
    {
        return AssetManager::GetAsset(m_Key);
    }
}
