#ifndef CHAKRA_RENDERER_IRENDER_MESH_HPP
#define CHAKRA_RENDERER_IRENDER_MESH_HPP

#include "core/Common.hpp"

namespace Chakra
{
    class IRenderMesh
    {
    public:
        virtual ~IRenderMesh() = default;

        virtual void Load(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<uint32_t> indices) = 0;
        virtual void Unload() = 0;

        virtual void Use() = 0;
        virtual uint64_t GetVertexCount() = 0;
    };
}

#endif
