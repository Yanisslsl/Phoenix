#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "Base/Base.h"

namespace Phoenix
{
    /**
     * \brief  Base class for creators
     * \tparam BaseType The type of the class that will be created
     * \tparam Args Arguments passed to the constructor  
     */
    template<typename BaseType, typename... Args>
    class BaseCreator
    {
    public:
        using BasePtr = std::shared_ptr<BaseType>;

        virtual ~BaseCreator() = default;
        virtual BasePtr Create(Args&&... args) = 0;
    };


    template<typename BaseType, typename DerivedType, typename... Args>
    class DerivedCreator final: public BaseCreator<BaseType, Args...>
    {
    public:
        typename BaseCreator<BaseType, Args...>::BasePtr Create(Args&&... args) override
        {
            return std::make_shared<DerivedType>(std::forward<Args>(args)...);
        }
    };

    
    template<typename Key, typename BaseType, typename... Args>
    class AbstractFactory
    {
    public:
        using BasePtr = std::shared_ptr<BaseType>;
        using CreatorPtr = std::shared_ptr<BaseCreator<BaseType, Args...>>;

    public:
        AbstractFactory() = default;
        virtual ~AbstractFactory() = default;

        template<typename RegisteredType>
        void RegisterType(const Key& key)
        {
            if (m_creators.find(key) != m_creators.end())
            {
                PX_CORE_ASSERT(false, "Key already exists in factory");
                return;
            }
            m_creators[key] = std::make_shared<DerivedCreator<BaseType, RegisteredType, Args...>>();
        }

        BasePtr Create(const Key& key, Args&&... args) const
        {
            if(m_creators.find(key) == m_creators.end())
            {
                PX_CORE_ASSERT(false, "Key not found in factory");
                return nullptr;
            }
            return m_creators.at(key)->Create(std::forward<Args>(args)...);
        }
        
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
