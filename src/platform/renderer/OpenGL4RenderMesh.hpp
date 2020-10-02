#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL3_RENDER_MESH_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL3_RENDER_MESH_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include "renderer/IRenderMesh.hpp"

#include "platform/renderer/OpenGL4Common.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Chakra
{
    class OpenGL4RenderMesh : public IRenderMesh
    {
    public:
        void Load(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<uint32_t> indices) override;
        void Unload() override;

        void Use() override;
        uint64_t GetVertexCount() override;

    private:
        GLuint m_MeshHandle;
        GLuint m_VertexCount;

        GLuint m_PositionHandle;
        GLuint m_UVHandle;
        GLuint m_NormalHandle;
        GLuint m_IndexHandle;
    };
}

#endif
