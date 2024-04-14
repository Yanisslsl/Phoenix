#pragma once
#include <functional>
#include <map>
#include <string>

#include "ComponentsData.h"
#include "EntityComponent.h"


namespace Phoenix
{
    /**
     * @brief AnimationData class
     * 
     */
    class AnimationData: public ComponentsData
    {
    public:
        AnimationData(size_t size);
        ComponentsDataType<std::string> m_currentAnimationNames;
        ComponentsDataType<std::map<std::string, float>> m_durations;
        ComponentsDataType<std::map<std::string, float>> m_currentTimes;
        ComponentsDataType<std::map<std::string, int>> m_currentFrames;
        ComponentsDataType<EntityId> m_entitiesIds;
        ComponentsDataType<std::map<std::string, int>> m_totalFrames;
        ComponentsDataType<std::vector<std::string>> m_names;
        ComponentsDataType<std::map<std::string, std::vector<std::string>>> m_texturesPaths;
        ComponentsDataType<std::map<std::string, std::function<void()>>> m_onAnimationEnd;
    };
}
