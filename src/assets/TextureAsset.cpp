#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "TextureAsset.hpp"

namespace Chakra
{
    TextureAsset::TextureAsset(const std::string & path, TextureData data)
    {
        Type = "TextureAsset";
        
        std::vector<char> fileData;

        {
            std::ifstream in(path, std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            fileData.resize(fileSize);

            in.seekg(0);
            in.read(fileData.data(), fileSize);            

            in.close();
        }

        int width, height, channels;

        unsigned char * pixelData = stbi_load_from_memory((unsigned char *)fileData.data(), fileData.size(), &width, &height, &channels, 0);

        for (int i = 0; i < width * height * channels; i++)
        {
            m_RawTexture.emplace_back(pixelData[i]);
        }

        stbi_image_free(pixelData);

        m_RenderTexture.Load(width, height, data, m_RawTexture);
    }

    TextureAsset::~TextureAsset()
    {
        m_RenderTexture.Unload();
    }
}
