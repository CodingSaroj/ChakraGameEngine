#ifndef CHAKRA_FILE_SYSTEM_HPP
#define CHAKRA_FILE_SYSTEM_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include <cstring>

namespace Chakra
{
    class FileSystem
    {
        public:
            static void      LoadIntoMemory(const std::string & path, const std::string & id);
            static void      FreeMemory(const std::string & id);
            static uint8_t * GetMemoryLocation(const std::string & id);
            static uint64_t  GetMemorySize(const std::string & id);

            static void SendToFile(const std::string & id, uint8_t * data, uint64_t size);

        private:
            static std::unordered_map<std::string, std::pair<uint8_t *, uint64_t>> fileMemoryLocations;
    };
}

#endif
