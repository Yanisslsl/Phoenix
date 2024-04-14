#include "ECS/include/AnimationData.h"

namespace Phoenix
{
    AnimationData::AnimationData(size_t size)
        : ComponentsData()
    {
        m_currentAnimationNames.resize(size);
        m_durations.resize(size);
        m_currentTimes.resize(size);
        m_currentFrames.resize(size);
        m_totalFrames.resize(size);
        m_names.resize(size);
        m_texturesPaths.resize(size);
        // set entitiesIds to -1
        m_entitiesIds.resize(size, -1);
        m_onAnimationEnd.resize(size);
    }
}
