#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/Endian.hpp"

struct MeshData
{
    std::string Name;

    std::vector<glm::vec3> Positions;
    std::vector<glm::vec2> UVs;
    std::vector<glm::vec3> Normals;
    std::vector<uint32_t> Indices;
};

static std::vector<MeshData> s_Meshes;

static std::string s_InputFile;

void PrintHelp()
{
    std::cout<<"Usage: chkmesh [FILE]\n\n";
    std::cout<<"FILE:\n";
    std::cout<<"    Input mesh file.\n";
}

void ParseCmdArgs(int argc, char * argv[])
{
    if (argc == 1)
    {
        PrintHelp();
        exit(2);
    }

    for (int i = 1; i < argc; i++)
    {
        s_InputFile = argv[i];
    }
}

void LoadMeshData()
{
    Assimp::Importer importer;        
    const aiScene * scene = importer.ReadFile(s_InputFile.c_str(), aiProcess_Triangulate);

    if (!scene)
    {
        std::cout<<"Assimp::"<<"Failed to load mesh from file `"<<s_InputFile<<"`.\n";
        exit(2);
    }

    s_Meshes.resize(scene->mNumMeshes);

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        s_Meshes[i].Name = scene->mMeshes[i]->mName.C_Str();
        s_Meshes[i].Positions.resize(scene->mMeshes[i]->mNumVertices);
        s_Meshes[i].UVs.resize(scene->mMeshes[i]->mNumVertices);
        s_Meshes[i].Normals.resize(scene->mMeshes[i]->mNumVertices);

        for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
        {
            s_Meshes[i].Positions[j] = glm::vec3(
                scene->mMeshes[i]->mVertices[j].x,
                scene->mMeshes[i]->mVertices[j].y,
                scene->mMeshes[i]->mVertices[j].z
            );

            s_Meshes[i].UVs[j] = glm::vec2(
                scene->mMeshes[i]->mTextureCoords[0][j].x,
                scene->mMeshes[i]->mTextureCoords[0][j].y
            );

            s_Meshes[i].Normals[j] = glm::vec3(
                scene->mMeshes[i]->mNormals[j].x,
                scene->mMeshes[i]->mNormals[j].y,
                scene->mMeshes[i]->mNormals[j].z
            );
        }

        s_Meshes[i].Indices.reserve(scene->mMeshes[i]->mNumFaces * 3);

        for (unsigned int j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
        {
            for (unsigned int k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; k++)
            {
                s_Meshes[i].Indices.emplace_back(scene->mMeshes[i]->mFaces[j].mIndices[k]);
            }
        }
    }

    importer.FreeScene();
}

void ExportCHKMeshes()
{
    for (auto & mesh : s_Meshes)
    {
        std::ofstream out(mesh.Name + ".chkmesh");

        out.write("CHKMESH", 8);
        
        uint64_t vertexCount = mesh.Positions.size();
        uint64_t indexCount = mesh.Indices.size();

        vertexCount = Chakra::Endian::SystemToLittle(vertexCount);
        indexCount = Chakra::Endian::SystemToLittle(indexCount);

        out.write((char *)&vertexCount, 8);
        out.write((char *)&indexCount, 8);

        for (glm::vec3 position : mesh.Positions)
        {
            float x = position.x;
            float y = position.y;
            float z = position.z;

            x = Chakra::Endian::SystemToLittle(x);
            y = Chakra::Endian::SystemToLittle(y);
            z = Chakra::Endian::SystemToLittle(z);

            out.write((char *)&x, 4);
            out.write((char *)&y, 4);
            out.write((char *)&z, 4);
        }

        for (glm::vec2 uv : mesh.UVs)
        {
            float x = uv.x;
            float y = uv.y;

            x = Chakra::Endian::SystemToLittle(x);
            y = Chakra::Endian::SystemToLittle(y);

            out.write((char *)&x, 4);
            out.write((char *)&y, 4);
        }

        for (glm::vec3 normal : mesh.Normals)
        {
            float x = normal.x;
            float y = normal.y;
            float z = normal.z;

            x = Chakra::Endian::SystemToLittle(x);
            y = Chakra::Endian::SystemToLittle(y);
            z = Chakra::Endian::SystemToLittle(z);

            out.write((char *)&x, 4);
            out.write((char *)&y, 4);
            out.write((char *)&z, 4);
        }

        for (uint32_t index : mesh.Indices)
        {
            index = Chakra::Endian::SystemToLittle(index);

            out.write((char *)&index, 4);
        }

        out.close();
    }
}

int main(int argc, char * argv[])
{
    ParseCmdArgs(argc, argv);

    LoadMeshData();
    ExportCHKMeshes();
}
