 #pragma once
 namespace Phoenix
 {
  using ComponentId = long long int;
  using ComponentSystemId = size_t;\
  using EntityId = size_t;
  // EntityIdExtended can be used for systems that need to store the entity id with unset values like -1
  using EntityIdExtended = long long int;
 }
