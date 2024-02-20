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
        //Comment forcer l'appel de ces méthodes par les enfants ComponentSystem
        void Init() override;
        void Start() override;
        void Update() override;

        void AddComponentTo(EntityId entity);

        virtual void InitComponents() = 0;
        virtual void StartComponents() = 0;
        virtual void UpdateComponents() = 0;

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

