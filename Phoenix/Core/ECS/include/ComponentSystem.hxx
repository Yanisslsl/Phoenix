// #pragma once
// #include "EntityManager.h"
// #include "ComponentSystem.h"
//
//     template <class C>
//     void Phoenix::ComponentSystem<C>::Init()
//     {
//         ISystem::Init();
//         InitComponents();
//     }
//
//     template <class C>
//     void Phoenix::ComponentSystem<C>::Start()
//     {
//         ISystem::Start();
//         StartComponents();
//     }
//
//     template <class C>
//     void Phoenix::ComponentSystem<C>::Update()
//     {
//         ISystem::Update();
//         UpdateComponents();
//     }
//
//     template <class C>
//     void ::Phoenix::ComponentSystem<C>::AddComponentTo(EntityId entity)
//     {
//         //Ajouter à l'entityManager le componentId pour l'entité 
//         const auto it = std::adjacent_find(begin(m_ComponentsId), end(m_ComponentsId),
//         [](ComponentId lhs, ComponentId rhs){ return (lhs+1 != rhs); });
//         if (it == end(m_ComponentsId))
//         {
//             m_ComponentsId.push_back(m_ComponentsId.size());
//             EntityMgr.   PrintEntityName(entity);
//             //To Do : Call Init ?
//             return m_ComponentsId.back();
//         }
//         else
//         {
//             const auto result = m_ComponentsId.insert(it+1, (*it)+1);
//             //To Do : Call Init ?
//             return m_ComponentsId.at((*result));
//         }
//     }
//
//     template <class C>
//     ::Phoenix::ComponentSystem<C>::ComponentSystem(ComponentSystemId id):m_Id(id)
//     {
//     }
//
//
