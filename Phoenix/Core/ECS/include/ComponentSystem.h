#pragma once
#include <vector>

#include "EntityComponent.h"
#include "ISystem.h"
#include "Core.h"


namespace Phoenix
{
    /**
     * @brief Base class for all component systems
     *        Each base class must implement the InitComponents, StartComponents and UpdateComponents methods
     *        This class holds number entities that have the the specific component
     */
    class PHOENIX_API ComponentSystem
        : public ISystem
    {
    public:
        void Init() override;
        void Start() override;
        void Update() override;

        void AddComponentTo(EntityId entity);
        virtual void DeleteComponent(EntityId entity);
        virtual void InitComponents() = 0;
        virtual void StartComponents() = 0;
        virtual void UpdateComponents() = 0;

        ComponentSystem(size_t id, size_t dataSize)
            : m_Id(id)
        {
            m_ComponentsId.reserve(dataSize);
        }
        ~ComponentSystem() noexcept
        {
        }
        
    protected:
        ComponentSystemId m_Id;
    private:
        std::vector<ComponentId> m_ComponentsId;
    };
}

