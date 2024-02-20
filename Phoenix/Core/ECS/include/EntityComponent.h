 #pragma once
 namespace Phoenix
 {
  using ComponentId = size_t;
  using ComponentSystemId = size_t;
  using EntityId = size_t;
 }
// #include <any>
// #include <map>
// #include <string>
//
// #include "Component.h"
// #include "Common/Core/Scene/include/Scene.h"
//
// namespace Phoenix
// {
//     using EntityId = size_t;
//
//     class PHOENIX_API Entity
//     {
//     public:
//         Entity() = delete;
//         Entity(size_t id, std::string name);
//
//         EntityId GetEntityId() const
//         {
//             return m_Id;
//         }
//
//         const std::string& GetEntityName() const
//         {
//             return m_Name;
//         }
//
//         ~Entity();
//
//     private:
//         std::string m_Name;
//         EntityId m_Id;
//
//
//     
//         // cannot use template data members on non static data members
//         std::map<std::string,IComponent> m_Components;
//         template <class T>
//         void AddComponent(T component);
//         template <class T>
//         T& GetComponent();
//         template <class T>
//         bool HasComponent();
//         template <class T>
//         void OnComponentAdded(T component);
//         template <class>
//         void OnComponentAdded(Phoenix::SpriteComponent component);
//         template <class>
//         void OnComponentAdded(Phoenix::TransformComponent component);
//     };
// }
