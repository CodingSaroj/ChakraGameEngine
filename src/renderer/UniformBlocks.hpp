#ifndef CHAKRA_RENDERER_UNIFORM_BLOCKS_HPP
#define CHAKRA_RENDERER_UNIFORM_BLOCKS_HPP

#include "core/Common.hpp"

#include "renderer/IUniformBlocks.hpp"

#if CHK_GRAPHICS_API == OpenGL4
    #include "platform/renderer/OpenGL4UniformBlocks.hpp"
#endif

namespace Chakra
{
    class UniformBlocks : public IUniformBlocks
    {
    public:
        UniformBlocks();
        ~UniformBlocks();

        void CreateUniformBlock(const std::string & id, uint64_t blockSize) override;
        void UpdateUniformBlock(const std::string & id, uint64_t offset, void * data, uint64_t blockSize) override;
        void DestroyUniformBlocks() override;

        uint64_t GetBindingPoint(const std::string & id) override;

    private:
        IUniformBlocks * m_UniformBlocks;
    };
}

#endif
