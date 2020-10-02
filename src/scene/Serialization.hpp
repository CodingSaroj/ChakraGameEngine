#ifndef CHAKRA_SCENE_SERIALIZATION_HPP
#define CHAKRA_SCENE_SERIALIZATION_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include "scene/Scene.hpp"

#include <yaml-cpp/yaml.h>

namespace Chakra
{
    class Serializer
    {
    public:
        std::string Serialize(Entity & entity, YAML::Emitter & emitter, bool standalone = true);
        std::string Serialize(Scene & scene);

        void DeserializeEntity(Entity & entity, const std::string & data);
        void DeserializeEntity(Entity & entity, YAML::Node data);
        void DeserializeScene(Scene & scene, const std::string & data);
    };
}

#endif
