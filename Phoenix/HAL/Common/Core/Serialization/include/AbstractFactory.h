#pragma once
#include "Common/Core/ECSExtended/include/TransformSubsytem.h"

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
        using BasePtr = std::unique_ptr<BaseType>;

        virtual ~BaseCreator() = default;
        virtual BasePtr Create(Args&&... args) = 0;
    };


    template<typename BaseType, typename DerivedType, typename... Args>
    class DerivedCreator final: public BaseCreator<BaseType, Args...>
    {
    public:
        typename BaseCreator<BaseType, Args...>::BasePtr Create(Args&&... args) override
        {
            return std::make_unique<DerivedType>(std::forward<Args>(args)...);
        }
    };

    
    template<typename Key, typename BaseType, typename... Args>
    class AbstractFactory
    {
    public:
        using BasePtr = std::unique_ptr<BaseType>;
        using CreatorPtr = std::unique_ptr<BaseCreator<BaseType, Args...>>;

    public:
        AbstractFactory() = default;
        virtual ~AbstractFactory() = default;

        template<typename RegisteredType>
        void RegisterType(const Key& key);

        BasePtr Create(const Key& key, Args&&... args) const;
        std::vector<Key> RegisteredTypes() const;
    private:
        std::unordered_map<Key, CreatorPtr> m_creators;
    };
}
