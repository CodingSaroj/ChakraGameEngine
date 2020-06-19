#include "FileSystem.hpp"

namespace Chakra
{
    std::unordered_map<std::string, std::pair<uint8_t *, uint64_t>> FileSystem::fileMemoryLocations;
    
    void FileSystem::LoadIntoMemory(const std::string & path, const std::string & id)
    {
        std::ifstream file(path);
    
        std::stringstream rawStream;
    
        rawStream<<file.rdbuf();
    
        file.close();
    
        std::string rawStr = rawStream.str();
    
        uint8_t * rawData = new uint8_t[rawStr.size()];
        memcpy(rawData, rawStr.c_str(), rawStr.size());
    
        fileMemoryLocations[id] = std::pair<uint8_t *, uint64_t>(rawData, rawStr.size());
    }
    
    void FileSystem::FreeMemory(const std::string & id)
    {
        delete [] fileMemoryLocations[id].first;
    }
    
    uint8_t * FileSystem::GetMemoryLocation(const std::string & id)
    {
        return fileMemoryLocations[id].first;
    }
    
    uint64_t FileSystem::GetMemorySize(const std::string & id)
    {
        return fileMemoryLocations[id].second;
    }
    
    void FileSystem::SendToFile(const std::string & path, uint8_t * data, uint64_t size)
    {
        std::ofstream file(path);
    
        file.write((const char *)data, size);
    
        file.close();
    }
}
