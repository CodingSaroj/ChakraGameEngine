#include "AssetManager.hpp"

namespace Chakra
{
    std::unordered_map<std::string, std::function<Asset *(BinaryData &&)>> AssetManager::binFileExtensions;
    std::unordered_map<std::string, std::function<Asset *(TextData &&)>>   AssetManager::txtFileExtensions;
    std::unordered_map<std::string, std::function<Asset *(XMLTree &&)>>    AssetManager::xmlFileExtensions;
    std::unordered_map<std::string, Asset *>                               AssetManager::assets;
    
    bool AssetManager::CheckExtRegistered(const std::string & ext)
    {
        if (binFileExtensions.count(ext) > 0)
        {
            Logger::LogWarning("AssetManager", std::string("File extension ") + ext + " is already registered.");
            return true;
        }
        else if (txtFileExtensions.count(ext) > 0)
        {
            Logger::LogWarning("AssetManager", std::string("File extension ") + ext + " is already registered.");
            return true;
        }
        else if (xmlFileExtensions.count(ext) > 0)
        {
            Logger::LogWarning("AssetManager", std::string("File extension ") + ext + " is already registered.");
            return true;
        }
    
        return false;
    }
    
    void AssetManager::RegisterBinaryFileExtension(
                    const std::string & ext,
                    std::function<Asset *(BinaryData &&)> loadFunction)
    {
        if (CheckExtRegistered(ext))
        {
            return;
        }
    
        binFileExtensions[ext] = loadFunction;
    }
    
    void AssetManager::RegisterTextFileExtension(
                    const std::string & ext,
                    std::function<Asset *(TextData &&)> loadFunction)
    {
        if (CheckExtRegistered(ext))
        {
            return;
        }
    
        txtFileExtensions[ext] = loadFunction;
    }
    
    void AssetManager::RegisterXMLFileExtension(
                    const std::string & ext,
                    std::function<Asset *(XMLTree &&)> loadFunction)
    {
        if (CheckExtRegistered(ext))
        {
            return;
        }
    
        xmlFileExtensions[ext] = loadFunction;
    }
    
    void AssetManager::Load(const std::string & key, const std::string & path)
    {
        std::string ext("*.");
    
        if (path.find('.') == 0)
        {
            ext = "<no_ext>";
        }
        else
        {
            for (int i = path.find_last_of('.') + 1; i < path.size(); i++)
            {
                ext.push_back(path[i]);
            }
        }
    
        FileSystem::LoadIntoMemory(path, key);
    
        if (binFileExtensions.count(ext) == 1)
        {
            LoadBinary(key, std::string((const char *)FileSystem::GetMemoryLocation(key), FileSystem::GetMemorySize(key)));
        }
        else if (txtFileExtensions.count(ext) == 1)
        {
            LoadText(key, std::string((const char *)FileSystem::GetMemoryLocation(key), FileSystem::GetMemorySize(key)));
        }
        else if (xmlFileExtensions.count(ext) == 1)
        {
            LoadXML(key, FileSystem::GetMemoryLocation(key));
        }
        else
        {
            Logger::LogWarning("AssetManager", "Trying to load asset with unregistered file extension");
        }
    
        FileSystem::FreeMemory(key);
    }
    
    Asset * AssetManager::GetAsset(const std::string & key)
    {
        return assets[key];
    }
    
    void AssetManager::LoadBinary(const std::string & key, const std::string & data)
    {
        assets[key] = new BinaryData(data);
    }
    
    void AssetManager::LoadText(const std::string & key, const std::string & data)
    {
        assets[key] = new TextData(data);
    }
    
    void AssetManager::LoadXML(const std::string & key, uint8_t * rawData)
    {
        XML::Reader reader((const char *)rawData);
        assets[key] = new XMLTree(reader.getRootNode());
    }
}
