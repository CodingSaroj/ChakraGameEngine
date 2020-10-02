#ifndef CHAKRA_ASSETS_TEXTURE_ASSET_HPP
#define CHAKRA_ASSETS_TEXTURE_ASSET_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"
#include "core/Asset.hpp"

#include "renderer/Texture.hpp"

namespace Chakra
{
    class TextureAsset : public Asset
    {
    public:
        TextureAsset(const std::string & path, TextureData importSettings);
        ~TextureAsset();

        constexpr Texture & GetRenderTexture() { return m_RenderTexture; }

    private:
        std::vector<uint8_t> m_RawTexture;
        Texture m_RenderTexture;
    };
}

#endif
