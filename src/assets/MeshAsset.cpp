#include "MeshAsset.hpp"

namespace  Chakra
{
    MeshAsset::MeshAsset(const std::string & path, MeshAssetImportSettings importSettings)
        : m_RenderMeshCreated(importSettings.UseForRenderMesh)
    {
        {
            std::ifstream in(path, std::ios_base::binary);

            CHK_ASSERT(in.is_open(), "AssetManager", "Failed to load file `", path, "`: ", strerror(errno), ".");

            char signature[8];
            in.read(signature, 8);

            CHK_ASSERT(std::string(signature) == "CHKMESH", "File `", path, "` is not a CHKMESH file.");

            uint64_t vertexCount, indexCount;
            in.read((char *)&vertexCount, 8);
            in.read((char *)&indexCount, 8);

            for (uint64_t i = 0; i < vertexCount; i++)
            {
                glm::vec3 position(0.0f);
                in.read((char *)&position.x, 4);
                in.read((char *)&position.y, 4);
                in.read((char *)&position.z, 4);

                position.x = Endian::LittleToSystem(position.x);
                position.y = Endian::LittleToSystem(position.y);
                position.z = Endian::LittleToSystem(position.z);

                m_Positions.emplace_back(position);
            }

            for (uint64_t i = 0; i < vertexCount; i++)
            {
                glm::vec2 uv(0.0f);
                in.read((char *)&uv.x, 4);
                in.read((char *)&uv.y, 4);

                uv.x = Endian::LittleToSystem(uv.x);
                uv.y = Endian::LittleToSystem(uv.y);

                m_UVs.emplace_back(uv);
            }

            for (uint64_t i = 0; i < vertexCount; i++)
            {
                glm::vec3 normal(0.0f);
                in.read((char *)&normal.x, 4);
                in.read((char *)&normal.y, 4);
                in.read((char *)&normal.z, 4);

                normal.x = Endian::LittleToSystem(normal.x);
                normal.y = Endian::LittleToSystem(normal.y);
                normal.z = Endian::LittleToSystem(normal.z);

                m_Normals.emplace_back(normal);
            }

            for (uint64_t i = 0; i < indexCount; i++)
            {
                uint32_t index = 0;
                in.read((char *)&index, 4);

                index = Endian::LittleToSystem(index);

                m_Indices.emplace_back(index);
            }

            in.close();
        }

        if (importSettings.UseForRenderMesh)
        {
            m_RenderMesh.Load(m_Positions, m_UVs, m_Normals, m_Indices);
        }
    }

    MeshAsset::~MeshAsset()
    {
        if (m_RenderMeshCreated)
        {
            m_RenderMesh.Unload();
        }
    }
}
