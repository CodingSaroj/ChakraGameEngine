#ifndef CHAKRA_ASSETS_HPP
#define CHAKRA_ASSETS_HPP

#include "core/Asset.hpp"

namespace Chakra
{
    class Mesh : public Asset
    {
        public:
            Mesh(std::vector<float> &        vertices,
                 std::vector<float> &        uvs,
                 std::vector<float> &        normals,
                 std::vector<unsigned int> & indices);

            const std::vector<float> &        getVertices();
            const std::vector<float> &        getUVs();
            const std::vector<float> &        getNormals();
            const std::vector<unsigned int> & getIndices();

        private:
            std::vector<float>        m_Vertices;
            std::vector<float>        m_UVs;
            std::vector<float>        m_Normals;
            std::vector<unsigned int> m_Indices;
    };
}

#endif
