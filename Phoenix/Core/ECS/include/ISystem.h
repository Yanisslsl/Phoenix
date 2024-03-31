#pragma once

namespace Phoenix
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        /**
         * Init method for all systems
         */
        virtual void Init()=0;
        /**
         * Start method for all systems
         */
        virtual void Start()=0;
        /**
         * Update method for all Systems
         */
        virtual void Update()=0;
    };
}

