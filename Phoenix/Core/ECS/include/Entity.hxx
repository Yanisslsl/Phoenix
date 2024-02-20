#pragma once
#include "Entity.h"
#include "Common/Core/Scene/include/Scene.h"

template <typename T>
void Entity::AddComponent(T component)
{
    m_Components.insert(std::make_pair(typeid(T).name(), component));
    OnComponentAdded<T>(component);
}

template <typename T>
T& Entity::GetComponent()
{
    return m_Components.at(typeid(T).name()).as<T>();
}

template <typename T>
bool Entity::HasComponent()
{
    return m_Components.find(typeid(T).name()) != m_Components.end();
}

template <typename T>
void Entity::OnComponentAdded(T component)
{
    static_assert(sizeof(T) == 0, "Component not found");
}

template <typename>
void Entity::OnComponentAdded(Phoenix::SpriteComponent component)
{
    auto c = component;
}

template <typename>
void Entity::OnComponentAdded(Phoenix::TransformComponent component)
{
    Phoenix::Renderer::UpdateShapeTransform(m_Name, component.GetTransformPosition());
}