#ifndef CHAKRA_ASSET_REF_HPP
#define CHAKRA_ASSET_REF_HPP

#include "core/Common.hpp"

#include "core/Asset.hpp"
#include "core/AssetManager.hpp"

namespace Chakra
{
    class AssetRef
    {
        public:
            AssetRef(const std::string & key);

            Asset * follow();

        private:
            std::string m_Key;
    };
}

#endif
