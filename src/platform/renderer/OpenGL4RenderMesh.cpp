#include "OpenGL4RenderMesh.hpp"

namespace Chakra
{
    void OpenGL4RenderMesh::Load(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<uint32_t> indices)
    {
        std::vector<GLuint> indicesGL(indices.begin(), indices.end());

        CHK_GL_CALL(glGenVertexArrays(1, &m_MeshHandle));

        CHK_GL_CALL(glBindVertexArray(m_MeshHandle));

        CHK_GL_CALL(glGenBuffers(1, &m_PositionHandle));
        CHK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_PositionHandle));
        CHK_GL_CALL(glBufferData(GL_ARRAY_BUFFER, positions.size() * 3 * sizeof(GLfloat), positions.data(), GL_STATIC_DRAW));

        CHK_GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *)0));
        CHK_GL_CALL(glEnableVertexAttribArray(0));

        CHK_GL_CALL(glGenBuffers(1, &m_UVHandle));
        CHK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_UVHandle));
        CHK_GL_CALL(glBufferData(GL_ARRAY_BUFFER, uvs.size() * 2 * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW));

        CHK_GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (const void *)0));
        CHK_GL_CALL(glEnableVertexAttribArray(1));

        CHK_GL_CALL(glGenBuffers(1, &m_NormalHandle));
        CHK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_NormalHandle));
        CHK_GL_CALL(glBufferData(GL_ARRAY_BUFFER, normals.size() * 3 * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW));

        CHK_GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *)0));
        CHK_GL_CALL(glEnableVertexAttribArray(2));

        CHK_GL_CALL(glGenBuffers(1, &m_IndexHandle));
        CHK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexHandle));
        CHK_GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesGL.size() * sizeof(GLuint), indicesGL.data(), GL_STATIC_DRAW));

        CHK_GL_CALL(glBindVertexArray(0));

        m_VertexCount = indicesGL.size();
    }

    void OpenGL4RenderMesh::Unload()
    {
        CHK_GL_CALL(glDeleteBuffers(1, &m_IndexHandle));
        CHK_GL_CALL(glDeleteBuffers(1, &m_NormalHandle));
        CHK_GL_CALL(glDeleteBuffers(1, &m_UVHandle));
        CHK_GL_CALL(glDeleteBuffers(1, &m_PositionHandle));

        CHK_GL_CALL(glDeleteVertexArrays(1, &m_MeshHandle));
    }

    void OpenGL4RenderMesh::Use()
    {
        CHK_GL_CALL(glBindVertexArray(m_MeshHandle));
    }

    uint64_t OpenGL4RenderMesh::GetVertexCount()
    {
        return m_VertexCount;
    }
}
