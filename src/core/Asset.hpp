#ifndef CHAKRA_ASSET_HPP
#define CHAKRA_ASSET_HPP

namespace Chakra
{
    enum class AssetMetaType
    {
        BinaryData,
        TextData,
        XMLTree,
        Custom
    };

    class Asset
    {
        public:
            Asset(AssetMetaType metaType);

        private:
            AssetMetaType m_MetaType;
    };
}

#endif
