#include "ShaderAsset.hpp"

namespace Chakra
{
    ShaderAsset::ShaderAsset(const std::string & path, ShaderAssetImportSettings importSettings)
    {
        Type = "ShaderAsset";

        std::array<std::vector<uint32_t>, 6> spirvBinaries;

        if (importSettings.Vertex)
        {
            std::ifstream in(path + ".vert.spv", std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            spirvBinaries[0].resize(fileSize / sizeof(uint32_t));

            in.seekg(0);
            in.read((char *)spirvBinaries[0].data(), fileSize);

            in.close();
        }
 
        if (importSettings.TessellationControl)
        {
            std::ifstream in(path + ".tesc.spv", std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            spirvBinaries[1].resize(fileSize / sizeof(uint32_t));

            in.seekg(0);
            in.read((char *)spirvBinaries[1].data(), fileSize);

            in.close();
        }

        if (importSettings.TessellationEvaluation)
        {
            std::ifstream in(path + ".tese.spv", std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            spirvBinaries[2].resize(fileSize / sizeof(uint32_t));

            in.seekg(0);
            in.read((char *)spirvBinaries[2].data(), fileSize);

            in.close();
        }

        if (importSettings.Geometry)
        {
            std::ifstream in(path + ".geom.spv", std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            spirvBinaries[3].resize(fileSize / sizeof(uint32_t));

            in.seekg(0);
            in.read((char *)spirvBinaries[3].data(), fileSize);

            in.close();
        }

        if (importSettings.Fragment)
        {
            std::ifstream in(path + ".frag.spv", std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            spirvBinaries[4].resize(fileSize / sizeof(uint32_t));

            in.seekg(0);
            in.read((char *)spirvBinaries[4].data(), fileSize);

            in.close();
        }
    
        if (importSettings.Compute)
        {
            std::ifstream in(path + ".comp.spv", std::ios_base::ate | std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            size_t fileSize = in.tellg();
            spirvBinaries[5].resize(fileSize / sizeof(uint32_t));

            in.seekg(0);
            in.read((char *)spirvBinaries[5].data(), fileSize);

            in.close();
        }

        m_Shader.Load({std::move(spirvBinaries[0]), std::move(spirvBinaries[1]), std::move(spirvBinaries[2]), std::move(spirvBinaries[3]), std::move(spirvBinaries[4]), std::move(spirvBinaries[5])});
    }

    ShaderAsset::~ShaderAsset()
    {
        m_Shader.Unload();
    }
}
