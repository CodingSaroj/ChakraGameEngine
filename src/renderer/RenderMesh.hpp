#ifndef CHAKRA_RENDERER_RENDER_MESH_HPP
#define CHAKRA_RENDERER_RENDER_MESH_HPP

#include "core/Common.hpp"

#include "renderer/IRenderMesh.hpp"

#if CHK_GRAPHICS_API == OpenGL4
    #include "platform/renderer/OpenGL4RenderMesh.hpp"
#endif

namespace Chakra
{
    class RenderMesh : public IRenderMesh
    {
    public:
        RenderMesh();
        ~RenderMesh();

        void Load(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<uint32_t> indices) override;
        void Unload() override;

        void Use() override;
        uint64_t GetVertexCount() override;

    private:
        IRenderMesh * m_RenderMesh;
    };
}

#endif
