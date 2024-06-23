 #pragma once
#include <entt/entity/entity.hpp>

 namespace Phoenix
 {
  using ComponentId = long long int;
  using ComponentSystemId = size_t;
  // EntityId is a long long int because -1 is used to represent an invalid entity
  using EntityId = long long int;
  using EntityIdentifier = entt::entity;
 }
