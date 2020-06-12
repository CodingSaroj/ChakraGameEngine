#ifndef CHAKRA_ASSET_HPP
#define CHAKRA_ASSET_HPP

namespace Chakra
{
    enum class AssetType
    {
        MeshBMSF
    };

    class Asset
    {
        public:
            Asset(AssetType type);

        private:
            AssetType m_Type;
    };
}

#endif
