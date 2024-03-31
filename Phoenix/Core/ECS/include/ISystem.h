#pragma once

namespace Phoenix
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        /**
         * \brief Init method for all systems
         */
        virtual void Init()=0;
        /**
         * \brief Start method for all systems
         */
        virtual void Start()=0;
        /**
         * \brief Update method for all Systems
         */
        virtual void Update()=0;
    };
}

