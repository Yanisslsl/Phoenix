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
         * \brief Init method for all component systems
         */
        void Init() override;
        /**
         * \brief Start method for all component systems
         */
        void Start() override;
        /**
         * \brief Update method for all component systems
         */
        void Update() override;

        /**
         * \brief Add the component to the passed entity
         */
        void AddComponentTo(EntityId entity);
        /**
         * \brief Remove the component from the passed entity
         */
        virtual void DeleteComponent(EntityId entity);
        /**
         * \brief Init method for all components of the system
         */
        virtual void InitComponents() = 0;
        /**
         * \brief Start method for all components of the system
         */
        virtual void StartComponents() = 0;
        /**
         * \brief Update method for all components of the system
         */
        virtual void UpdateComponents() = 0;

        /**
         * \brief Create a component system with his id and the number of component it can handle
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

