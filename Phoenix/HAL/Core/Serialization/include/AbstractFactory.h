#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "Base/Base.h"

namespace Phoenix
{
    /**
     * \brief  Base class for creators
     * \tparam BaseType The BASE type of the class that will be created
     * \tparam Args Arguments passed to the constructor  
     */
    template<typename BaseType, typename... Args>
    class BaseCreator
    {
    public:
        using BasePtr = std::shared_ptr<BaseType>;

        virtual ~BaseCreator() = default;
        /** 
         * \brief Create a new instance of the based class
         * \param args Arguments passed to the constructor
         * \return A shared pointer to the created object
         */
        virtual BasePtr Create(Args&&... args) = 0;
    };


    /** 
     * \brief Derived Creator class
     * \tparam BaseType The BASE type of the class that will be created
     * \tparam DerivedType The DERIVED type of the class that will be created
     * \tparam Args Arguments passed to the constructor
     */
    template<typename BaseType, typename DerivedType, typename... Args>
    class DerivedCreator final: public BaseCreator<BaseType, Args...>
    {
    public:

        /** 
         * \brief Create a new instance of the derived class
         * \param args Arguments passed to the constructor
         * \return A shared pointer to the created object
         */
        typename BaseCreator<BaseType, Args...>::BasePtr Create(Args&&... args) override
        {
            return std::make_shared<DerivedType>(std::forward<Args>(args)...);
        }
    };


    /** 
     * \brief Abstract Factory class
     * \tparam Key The key type used to identify the type
     * \tparam BaseType The BASE type of the class that will be created
     * \tparam Args Arguments passed to the constructor
     */
    template<typename Key, typename BaseType, typename... Args>
    class AbstractFactory
    {
    public:
        using BasePtr = std::shared_ptr<BaseType>;
        using CreatorPtr = std::shared_ptr<BaseCreator<BaseType, Args...>>;

    public:
        AbstractFactory() = default;
        virtual ~AbstractFactory() = default;

        /** 
         * \brief Register a new type in the factory
         * \tparam RegisteredType The type to register
         * \param key The key to identify the type
         */
        template<typename RegisteredType>
        void RegisterType(const Key& key)
        {
            if (m_creators.find(key) != m_creators.end())
            {
                PX_ERROR("Key already exists in factory");
                return;
            }
            m_creators[key] = std::make_shared<DerivedCreator<BaseType, RegisteredType, Args...>>();
        }

        /** 
         * \brief Create a new instance of the registered type
         * \param key The key to identify the type
         * \param args Arguments passed to the constructor
         * \return A shared pointer to the created object
         */
        BasePtr Create(const Key& key, Args&&... args) const
        {
            if(m_creators.find(key) == m_creators.end())
            {
                PX_ERROR("Key not found in factory");
                return nullptr;
            }
            return m_creators.at(key)->Create(std::forward<Args>(args)...);
        }

        /** 
         * \brief Get all the registered types
         * \return A vector of keys
         */
        std::vector<Key> RegisteredTypes() const
        {
            std::vector<Key> keys;
            for(auto& [key, _] : m_creators)
            {
                keys.push_back(key);
            }
            return keys;
        }
    private:
        std::unordered_map<Key, CreatorPtr> m_creators;
    };
}
