// Tag.h

#pragma once
#include <string>

#include "Core.h"
#include "Base/Base.h"

namespace Phoenix
{
    using TagType = uint32_t;

    namespace Tag
    {
        PHOENIX_API enum : TagType
        {
            None = 0,
            Player = BIT(1),
            Bullet = BIT(2),
            Mob = BIT(3),
        };
    }

    class PHOENIX_API Tags
    {
    public:
        inline static TagType AddTag(TagType newTag, TagType currentTag = 0)
        {
            return currentTag | newTag;
        }

        inline static TagType RemoveTag(TagType currentTag, TagType tagToRemove)
        {
            return currentTag & ~tagToRemove;
        }

        inline static bool HasTag(TagType currentTag, TagType tagToCheck)
        {
            return currentTag & tagToCheck;
        }
    };
}
