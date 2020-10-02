#include "OpenGL4UniformBlocks.hpp"

namespace Chakra
{
    void OpenGL4UniformBlocks::CreateUniformBlock(const std::string & id, uint64_t blockSize)
    {
        if (m_UniformBlocks.count(id))
        {
            CHK_WARNING("Renderer::OpenGL4", "Uniform block already exists with id `", id, "`.");
            return;
        }

        static GLuint currentBindPoint = 0;

        CHK_GL_CALL(glGenBuffers(1, &m_UniformBlocks[id].second));
        CHK_GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBlocks[id].second));
        CHK_GL_CALL(glBufferData(GL_UNIFORM_BUFFER, blockSize, nullptr, GL_DYNAMIC_DRAW));
        CHK_GL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, currentBindPoint, m_UniformBlocks[id].second));
        CHK_GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));

        m_UniformBlocks[id].first = currentBindPoint++;
    }

    void OpenGL4UniformBlocks::UpdateUniformBlock(const std::string & id, uint64_t offset, void * data, uint64_t blockSize)
    {
        CHK_GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBlocks[id].second));
        CHK_GL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, offset, blockSize, data));
        CHK_GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    }

    void OpenGL4UniformBlocks::DestroyUniformBlocks()
    {
        for (auto & uniformBlock : m_UniformBlocks)
        {
            CHK_GL_CALL(glDeleteBuffers(1, &uniformBlock.second.second));
        }
    }

    uint64_t OpenGL4UniformBlocks::GetBindingPoint(const std::string & id)
    {
        return m_UniformBlocks[id].first;
    }
}
