#pragma once
#include <algorithm>
#include <vector>

#include "ComponentsData.h"
#include "EntityComponent.h"
#include "ISystem.h"
#include "../../../Core/Core.h"


namespace Phoenix
{
    class PHOENIX_API ComponentSystem
        : public ISystem
    {
    public:
        /**
         * Init method for all component systems
         */
        void Init() override;
        /**
         * Start method for all component systems
         */
        void Start() override;
        /**
         * Update method for all component systems
         */
        void Update() override;

        /**
         * Add the component to the passed entity
         */
        void AddComponentTo(EntityId entity);
        /**
         * Remove the component from the passed entity
         */
        virtual void DeleteComponent(EntityId entity);
        /**
         * Init method for all components of the system
         */
        virtual void InitComponents() = 0;
        /**
         * Start method for all components of the system
         */
        virtual void StartComponents() = 0;
        /**
         * Update method for all components of the system
         */
        virtual void UpdateComponents() = 0;

        /**
         * Create a component system with his id and the number of component it can handle
         */
        ComponentSystem(size_t id, size_t dataSize)
            : m_Id(id)
        {
            m_ComponentsId.reserve(dataSize);
        }

        // runtime error when error occurs in the destructor
        ~ComponentSystem() noexcept
        {
        }
        
    protected:
        ComponentSystemId m_Id;
    private:
        std::vector<ComponentId> m_ComponentsId;
    };

  

    //#include "ComponentSystem.hxx"
}

