// Tag.h

#pragma once

#include "Core.h"
#include "Base/Base.h"

namespace Phoenix
{
    using TagType = uint32_t;

    namespace Tag
    {
        enum : TagType
        {
            None = 0,
            Player = BIT(1),
            Bullet = BIT(2),
            Mob = BIT(3),
        };
    }

    /**
     * \brief Tags class that contains helper functions to manipulate tags.
     */
    class PHOENIX_API Tags
    {
    public:
        /**
         * \brief Add a tag to the current tag.
         * \param newTag Tag to add
         * \param currentTag Current tag
         * \return TagType
         */
        inline static TagType AddTag(TagType newTag, TagType currentTag = 0)
        {
            return currentTag | newTag;
        }

        /**
         * \brief Remove a tag from the current tag.
         * \param currentTag Current tag
         * \param tagToRemove Tag to remove
         * \return TagType
         */
        inline static TagType RemoveTag(TagType currentTag, TagType tagToRemove)
        {
            return currentTag & ~tagToRemove;
        }

        /**
         * \brief Check if the current tag has a specific tag.
         * \param currentTag Current tag
         * \param tagToCheck Tag to check
         * \return bool
         */
        inline static bool HasTag(TagType currentTag, TagType tagToCheck)
        {
            return currentTag & tagToCheck;
        }
    };
}
