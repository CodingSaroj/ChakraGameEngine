#ifndef CHAKRA_ASSET_MANAGER_HPP
#define CHAKRA_ASSET_MANAGER_HPP

#include <iostream>
#include <unordered_map>

#include "core/Asset.hpp"

namespace Chakra
{
    class AssetManager
    {
        public:
            static void LoadMeshBMSF(std::string key, std::string path);

        private:
            static std::unordered_map<std::string, Asset *> assets;
    };
}

#endif
