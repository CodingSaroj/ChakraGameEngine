#ifndef CHAKRA_ASSET_MANAGER_HPP
#define CHAKRA_ASSET_MANAGER_HPP

#include "core/Common.hpp"

#include "core/Logger.hpp"
#include "core/filesystem/FileSystem.hpp"
#include "core/MetaAssets.hpp"

#include "xml/Reader.hpp"

namespace Chakra
{
    class AssetManager
    {
        public:
            static void RegisterBinaryFileExtension(
                            const std::string & ext,
                            std::function<Asset *(BinaryData &&)> loadFunction
                        );

            static void RegisterTextFileExtension(
                            const std::string & ext,
                            std::function<Asset *(TextData &&)> loadFunction
                        );

            static void RegisterXMLFileExtension(
                            const std::string & ext,
                            std::function<Asset *(XMLTree &&)> loadFunction
                        );

            static void Load(const std::string & key, const std::string & path);

            static Asset * GetAsset(const std::string & key);

        private:
            static std::unordered_map<std::string, std::function<Asset *(BinaryData &&)>> binFileExtensions;
            static std::unordered_map<std::string, std::function<Asset *(TextData &&)>>   txtFileExtensions;
            static std::unordered_map<std::string, std::function<Asset *(XMLTree &&)>>    xmlFileExtensions;
            static std::unordered_map<std::string, Asset *>           assets;

            static bool CheckExtRegistered(const std::string & key);

            static void LoadBinary(const std::string & key, const std::string & data);
            static void LoadText(const std::string & key, const std::string & data);
            static void LoadXML(const std::string & key, uint8_t * rawData);
    };
}

#endif
