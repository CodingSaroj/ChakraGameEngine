#ifndef CHAKRA_ASSETS_SHADER_ASSET_HPP
#define CHAKRA_ASSETS_SHADER_ASSET_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"
#include "core/Asset.hpp"

#include "renderer/Shader.hpp"

namespace Chakra
{
    struct ShaderAssetImportSettings
    {
        bool Vertex = false;
        bool TessellationControl = false;
        bool TessellationEvaluation = false;
        bool Geometry = false;
        bool Fragment = false;
        bool Compute = false;
    };

    class ShaderAsset : public Asset
    {
    public:
        ShaderAsset(const std::string & path, ShaderAssetImportSettings importSettings);
        ~ShaderAsset();

        constexpr Shader & GetShader() { return m_Shader; }

    private:
        Shader m_Shader;
    };
}

#endif
