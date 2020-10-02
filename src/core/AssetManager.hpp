#ifndef CHAKRA_CORE_ASSET_MANAGER_HPP
#define CHAKRA_CORE_ASSET_MANAGER_HPP

#include "core/Common.hpp"

#include "core/Asset.hpp"

namespace Chakra
{
    struct AssetReference
    {
        std::string Key;
    };

    class AssetManager
    {
    public:
        template <typename AssetType, typename ImportSettingsType>
        static void Load(const std::string & key, const std::string & path, ImportSettingsType importSettings)
        {
            s_Assets[key] = (Asset *)(new AssetType(path, importSettings));
        }

        template <typename AssetType>
        static AssetType * Get(const std::string & key)
        {
            if (s_Assets.count(key))
            {
                return (AssetType *)s_Assets[key];
            }
            else
            {
                return nullptr;
            }
        }

    private:
        static std::unordered_map<std::string, Asset *> s_Assets;
    };
}

#endif
