#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Assets.hpp"

namespace Chakra
{
    Mesh::Mesh( std::vector<Math::vec3> & positions,
                std::vector<Math::vec2> & uvs,
                std::vector<Math::vec3> & normals,
                std::vector<uint32_t> &   indices)
        : Asset(AssetMetaType::Custom), m_Positions(positions), m_UVs(uvs), m_Normals(normals), m_Indices(indices)
    {
    }
    
    std::vector<Math::vec3> Mesh::getPositions()
    {
        return m_Positions;
    }
    
    std::vector<Math::vec2> Mesh::getUVs()
    {
        return m_UVs;
    }
    
    std::vector<Math::vec3> Mesh::getNormals()
    {
        return m_Normals;
    }
    
    std::vector<uint32_t> Mesh::getIndices()
    {
        return m_Indices;
    }

    Texture::Texture(ChannelFormat channelFmt, uint64_t width, uint64_t height, uint8_t * pixels)
        : Asset(AssetMetaType::Custom), m_ChannelFmt(channelFmt), m_Width(width), m_Height(height)
    {
        m_Pixels = new uint8_t[width * height];
        memcpy(m_Pixels, pixels, width * height);
    }

    Texture::ChannelFormat Texture::getChannelFmt()
    {
        return m_ChannelFmt;
    }

    uint64_t Texture::getWidth()
    {
        return m_Width;
    }

    uint64_t Texture::getHeight()
    {
        return m_Height;
    }

    uint8_t * Texture::getPixels()
    {
        return m_Pixels;
    }

    Asset * LoadMesh(TextData && data)
    {
        std::vector<Math::vec3> positions;
        std::vector<Math::vec2> uvs;
        std::vector<Math::vec3> normals;
        std::vector<uint32_t>   indices;

        Assimp::Importer importer;
        
        const aiScene * scene = importer.ReadFileFromMemory(
                                    data.getData().c_str(),
                                    data.getData().size(),
                                    aiProcess_Triangulate | aiProcess_FlipUVs
                                );

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Logger::LogError("Assimp", "Failed to load mesh");
            exit(-1);
        }

        aiMesh * mesh = nullptr;

        if (scene->mRootNode->mNumMeshes)
        {
            mesh = scene->mMeshes[scene->mRootNode->mMeshes[0]];
        }

        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            auto position = mesh->mVertices[i];
            auto uv       = mesh->mTextureCoords[i][0];
            auto normal   = mesh->mNormals[i];

            positions.push_back({ position.x, position.y, position.z });
            uvs.push_back({ uv.x, uv.y });
            normals.push_back({ normal.x, normal.y, normal.z });
        }

        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            for (int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        importer.FreeScene();

        return new Mesh(positions, uvs, normals, indices);
    }

    Asset * LoadTexture(BinaryData && data)
    {
        int channels, width, height;
        uint8_t * pixels = stbi_load_from_memory((const unsigned char *)data.getData().c_str(), data.getData().size(),
                                                 &width, &height, &channels, 0);

        Texture::ChannelFormat fmt;
        fmt = (Texture::ChannelFormat)channels;

        Texture * texture = new Texture(fmt, width, height, pixels);
        
        stbi_image_free(pixels);
        
        return texture;
    }

    void Setup()
    {
        AssetManager::RegisterTextFileExtension("*.obj", LoadMesh);
        AssetManager::RegisterBinaryFileExtension("*.png", LoadTexture);
    }
}
