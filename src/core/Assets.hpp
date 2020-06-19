#ifndef CHAKRA_ASSETS_HPP
#define CHAKRA_ASSETS_HPP

#include "core/Common.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/Asset.hpp"
#include "core/MetaAssets.hpp"
#include "core/AssetManager.hpp"

#include "math/Math.hpp"

namespace Chakra
{
    class Mesh : public Asset
    {
        public:
            Mesh( std::vector<Math::vec3> & positions,
                  std::vector<Math::vec2> & uvs,
                  std::vector<Math::vec3> & normals,
                  std::vector<uint32_t> &   indices);

            std::vector<Math::vec3> getPositions();
            std::vector<Math::vec2> getUVs();
            std::vector<Math::vec3> getNormals();
            std::vector<uint32_t>   getIndices();

        private:
            std::vector<Math::vec3>        m_Positions;
            std::vector<Math::vec2>        m_UVs;
            std::vector<Math::vec3>        m_Normals;
            std::vector<uint32_t>          m_Indices;
    };

    class Texture : public Asset
    {
        public:
            enum class ChannelFormat
            {
                R,
                RG,
                RGB,
                RGBA
            };

            Texture(ChannelFormat channelFmt, uint64_t width, uint64_t height, uint8_t * pixels);

            ChannelFormat getChannelFmt();
            uint64_t      getWidth();
            uint64_t      getHeight();
            uint8_t *     getPixels();

        private:
            ChannelFormat m_ChannelFmt;
            uint64_t      m_Width;
            uint64_t      m_Height;
            uint8_t *     m_Pixels;
    };

    void Setup();
}

#endif
