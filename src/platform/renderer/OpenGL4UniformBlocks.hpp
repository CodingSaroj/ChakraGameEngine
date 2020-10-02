#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL4_UNIFORM_BLOCKS_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL4_UNIFORM_BLOCKS_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include "renderer/IUniformBlocks.hpp"

#include "platform/renderer/OpenGL4Common.hpp"

#include <glad/glad.h>

namespace Chakra
{
    class OpenGL4UniformBlocks : public IUniformBlocks
    {
    public:
        void CreateUniformBlock(const std::string & id, uint64_t size) override;
        void UpdateUniformBlock(const std::string & id, uint64_t offset, void * data, uint64_t blockSize) override;
        void DestroyUniformBlocks() override;

        uint64_t GetBindingPoint(const std::string & id) override;

    private:
        std::unordered_map<std::string, std::pair<uint64_t, GLuint>> m_UniformBlocks;
    };
}

#endif
