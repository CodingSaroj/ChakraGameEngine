#ifndef CHAKRA_RENDERER_IUNIFORM_BLOCKS_HPP
#define CHAKRA_RENDERER_IUNIFORM_BLOCKS_HPP

#include "core/Common.hpp"

namespace Chakra
{
    class IUniformBlocks
    {
    public:
        virtual ~IUniformBlocks() = default;

        virtual void CreateUniformBlock(const std::string & id, uint64_t blockSize) = 0;
        virtual void UpdateUniformBlock(const std::string & id, uint64_t offset, void * data, uint64_t blockSize) = 0;
        virtual void DestroyUniformBlocks() = 0;

        virtual uint64_t GetBindingPoint(const std::string & id) = 0;
    };
}

#endif
