#pragma once
#include <vector>

#include "EntityComponent.h"



namespace Phoenix
{
    class ComponentSystem;
    
    /**
     * @brief Base class for all components data
     * 
     */ 
    class ComponentsData
    {
    public:
        friend ComponentSystem;
        virtual ~ComponentsData() = default;

        ComponentsData() = default;
    };

    template <typename T>
    class ComponentsDataType
    {
    public:
        void Add(T component)
        {
            m_components.push_back(component);
        }
        
        // We do not erase the component from the vector, we just set it to T()
        // This a decision made to avoid the overhead of moving all the elements in the vector after each deletion
        // But we got to keep in mind that the vector has fixed size, so we can't keep adding components without never reordering the vector
        //@TODO: Implement a way to resize the vector after a certain number of deleted components or after the size of the vector is reached
        void Remove(size_t index)
        {
            if(index < 0 || index >= m_components.size()) return;
            m_components[index] = T();
        }

        T& Get(size_t index)
        {
            return m_components[index];
        }

        size_t Size()
        {
            return m_components.size();
        }

        typename std::vector<T>::iterator begin()
        {
            return m_components.begin();
        }

        void resize(size_t size)
        {
            m_components.resize(size);
        }

    private:
        std::vector<T> m_components;
    };
}

