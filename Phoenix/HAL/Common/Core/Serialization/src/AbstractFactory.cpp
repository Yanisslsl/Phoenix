#include "Common/Core/Serialization/include/AbstractFactory.h"
#include "Common/Core/Animation/include/AnimationSubsystem.h"
#include "Common/Core/Physics/include/CollisionSubSytem.h"
#include "Common/Core/Scene/include/Scene.h"
#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{
   template <typename Key, typename BaseType, typename... Args>
   template <typename RegisteredType>
   void AbstractFactory<Key, BaseType, Args...>::RegisterType(const Key& key)
   {
      if(m_creators.contains(key))
      {
         PX_CORE_ASSERT(false, "Key already exists in factory");
         return;
      }
      m_creators[key] = std::make_unique<DerivedCreator<BaseType, RegisteredType, Args...>>();
   }

   template <typename Key, typename BaseType, typename ... Args>
   typename AbstractFactory<Key, BaseType, Args...>::BasePtr AbstractFactory<Key, BaseType, Args...>::Create(
      const Key& key, Args&&... args) const
   {
      if(!m_creators.contains(key))
      {
         PX_CORE_ASSERT(false, "Key not found in factory");
         return;
      }
      m_creators.at(key)->Create(std::forward<Args>(args)...);
   }

   template <typename Key, typename BaseType, typename ... Args>
   std::vector<Key> AbstractFactory<Key, BaseType, Args...>::RegisteredTypes() const
   {
      std::vector<Key> keys;
      for(auto& [key, _] : m_creators)
      {
         keys.push_back(key);
      }
      return keys;
   }
}
