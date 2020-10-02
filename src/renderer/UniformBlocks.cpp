#include "UniformBlocks.hpp"

namespace Chakra
{
    UniformBlocks::UniformBlocks()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        m_UniformBlocks = new OpenGL4UniformBlocks();
    #endif
    }

    UniformBlocks::~UniformBlocks()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        delete (OpenGL4UniformBlocks *)m_UniformBlocks;
    #endif
    }

    void UniformBlocks::CreateUniformBlock(const std::string & id, uint64_t blockSize)
    {
        m_UniformBlocks->CreateUniformBlock(id, blockSize);
    }

    void UniformBlocks::UpdateUniformBlock(const std::string & id, uint64_t offset, void * data, uint64_t blockSize)
    {
        m_UniformBlocks->UpdateUniformBlock(id, offset, data, blockSize);
    }

    void UniformBlocks::DestroyUniformBlocks()
    {
        m_UniformBlocks->DestroyUniformBlocks();
    }

    uint64_t UniformBlocks::GetBindingPoint(const std::string & id)
    {
        return m_UniformBlocks->GetBindingPoint(id);
    }
}
