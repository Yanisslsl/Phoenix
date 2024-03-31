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
        
        // We do not erase the component from the vector, we just set it to T()
        // This a decision made to avoid the overhead of moving all the elements in the vector after each deletion
        // But we got to keep in mind that the vector has fixed size, so we can't keep adding components without never reordering the vector
        //@TODO: Implement a way to reorder the vector after a certain number of deleted components or after the size of the vector is reached
        void Remove(size_t index)
        {
            if(index < 0 || index >= m_components.size()) return;
            m_components[index] = T();
        }

        void Remove(size_t index, T value)
        {
            if(index < 0 || index >= m_components.size()) return;
            m_components[index] = value;
        }
        
        T& Get(size_t index)
        {
            return m_components[index];
        }

        void Set(size_t index, T value)
        {
            return m_components[index] = value;
        }

        size_t Size()
        {
            return m_components.size();
        }

        typename std::vector<T>::iterator begin()
        {
            return m_components.begin();
        }

        typename std::vector<T>::iterator end()
        {
            return m_components.end();
        }

        void resize(size_t size)
        {
            m_components.resize(size);
        }

        void resize(size_t size, T value)
        {
            m_components.resize(size, value);
        }

        bool Contains(size_t index)
        {
            return m_components[index] != T();
        }
    private:
        std::vector<T> m_components;
    };
}

