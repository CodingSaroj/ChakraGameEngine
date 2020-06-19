#include "Scene.hpp"

namespace Chakra
{
    Scene::Scene(std::string id)
        : m_ID(id)
    {
    }
    
    Entity & Scene::addEntity(const EntityID & name)
    {
        if (m_Entities.count(name) == 0)
        {
            m_Entities.insert(std::pair<EntityID, Entity>(name, Entity(name)));
        }
        else
        {
            Logger::LogWarning("Scene", "Trying to add entity with an existing id");        
        }
        return m_Entities.find(name)->second;
    }
    
    Entity & Scene::getEntity(const EntityID & name)
    {
        if (m_Entities.count(name) == 1)
        {
            return m_Entities.find(name)->second;
        }
        else
        {
            Logger::LogError("Scene", "Trying to get an unavailable entity");
            exit(-1);
        }
    }
    
    void Scene::removeEntity(const EntityID & name)
    {
        if (m_Entities.count(name) == 1)
        {
            m_Entities.erase(m_Entities.find(name));
        }
        else
        {
            Logger::LogWarning("Scene", "Trying to remove an unavailable entity");
        }
    }
    
    void Scene::addSystem(System * system)
    {
        m_Systems.emplace_back(system);
    }
    
    void Scene::Initialize()
    {
        for (System * system : m_Systems)
        {
            system->OnInitialize();
        }
    }
    
    void Scene::Update()
    {
        for (System * system : m_Systems)
        {
            system->OnUpdate();
        }
    }
    
    void Scene::Exit()
    {
        for (System * system : m_Systems)
        {
            system->OnExit();
        }
    }
}
