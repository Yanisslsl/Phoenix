#pragma once

namespace Phoenix
{
    /**
     * @brief Interface for all systems
     * 
     */
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void Init()=0;
        virtual void Start()=0;
        virtual void Update()=0;
    };
}

