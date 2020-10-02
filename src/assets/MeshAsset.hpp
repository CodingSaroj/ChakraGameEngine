#ifndef CHAKRA_ASSETS_MESH_ASSET_HPP
#define CHAKRA_ASSETS_MESH_ASSET_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"
#include "core/Endian.hpp"
#include "core/Asset.hpp"

#include "renderer/RenderMesh.hpp"

namespace Chakra
{
    struct MeshAssetImportSettings
    {
        bool UseForRenderMesh = false;
    };

    class MeshAsset : public Asset
    {
    public:
        MeshAsset(const std::string & path, MeshAssetImportSettings importSettings);
        ~MeshAsset();

        constexpr std::vector<glm::vec3> & GetPositions() { return m_Positions; }
        constexpr std::vector<glm::vec2> & GetUVs() { return m_UVs; }
        constexpr std::vector<glm::vec3> & GetNormals() { return m_Normals; }
        constexpr std::vector<uint32_t> & GetIndices() { return m_Indices; }
        constexpr RenderMesh & GetRenderMesh() { return m_RenderMesh; }

    private:
        bool m_RenderMeshCreated;

        std::vector<glm::vec3> m_Positions;
        std::vector<glm::vec2> m_UVs;
        std::vector<glm::vec3> m_Normals;
        std::vector<uint32_t> m_Indices;

        RenderMesh m_RenderMesh;
    };
}

#endif
