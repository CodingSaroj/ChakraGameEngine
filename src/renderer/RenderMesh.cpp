#include "RenderMesh.hpp"

namespace Chakra
{
    RenderMesh::RenderMesh()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        m_RenderMesh = new OpenGL4RenderMesh();
    #endif
    }

    RenderMesh::~RenderMesh()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        delete (OpenGL4RenderMesh *)m_RenderMesh;
    #endif
    }

    void RenderMesh::Load(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<uint32_t> indices)
    {
        m_RenderMesh->Load(positions, uvs, normals, indices);
    }

    void RenderMesh::Unload()
    {
        m_RenderMesh->Unload();
    }

    void RenderMesh::Use()
    {
        m_RenderMesh->Use();
    }

    uint64_t RenderMesh::GetVertexCount()
    {
        return m_RenderMesh->GetVertexCount();
    }
}
