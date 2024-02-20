#pragma once
#include <vector>

#include "EntityComponent.h"



namespace Phoenix
{
    class ComponentSystem;
    /**
     * The class all Components inherits from, should only be used as parent class.
     */
    class ComponentsData
    {
    public:
        friend ComponentSystem;
        virtual ~ComponentsData() = default;

        ComponentsData() = default;
    };
}

