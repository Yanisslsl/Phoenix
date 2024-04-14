# Phoenix
<!-- ABOUT THE PROJECT -->
## About The Project
Welcome to our 2D OpenGL Engine, a comprehensive and lightweight graphics engine developed as a student project. This engine is meticulously crafted using modern C++ and the powerful OpenGL API, aiming to provide an intuitive and efficient platform for creating 2D graphics applications.

The core of this engine is its 2D renderer, designed from the ground up to support a wide range of 2D graphics operations including sprite rendering, animations, text rendering, and basic UI elements.

<!-- GETTING STARTED -->
## Getting Started

### Installation

1. Install [Cmake](https://cmake.org/download/), and [vcpkg](https://vcpkg.io/en/getting-started)
2. Clone the repo
   ```sh
   git clone https://github.com/Yanisslsl/Phoenix.git
   ```
3. Create the build directory
      ```sh
      mkdir build
      ```
4. From the build directory generate the project with cmake
    ```sh
     cmake -DCMAKE_TOOLCHAIN_FILE=${Path_To_vcpkg}/vcpkg/scripts/buildsystems/vcpkg.cmake ..
     ```
5. Open the .sln file in the build directory

## Features

### Entity-Component System:
ECS data oriented design, allowing for efficient and flexible entity management.
### OpenGL-Based Rendering: 
Leverages OpenGL's rendering capabilities to offer high-performance graphics output, tailored for 2D environments.
### Extensible Framework: 
Designed with extensibility in mind, allowing for easy integration of additional features like particle systems, advanced animations, and more.
### Scalable Collision Detection:
BST based collision detection system, supporting efficient collision detection for a large number of entities.
### Editor UI:
Basic editor UI to create entities and components, visualize the entities and components. You can move the camera by pressing M.
## Architecture

`Phoenix/Core` - Contains the core engine components at the lowest level, including the event dispatcher, events, log system, utils class...

`Phoenix/HAL/Core` - Contains the core components of the Hardware Abstraction Layer, including the window, input, application, renderer, and more.

`Phoenix/HAL/Windows` - Contains the Windows-specific implementation of the HAL.


## Getting started

The engine is designed to be easy to use and integrate into your projects. You can set the application mode to Standalone mode to easily create entities and components.
The Standalone mode provides a lightweight, self-managed system that allows you to create entities and components without the need for taking care of the memory management.
Here is an example of how to create a simple entity with a sprite component and transform component in Standalone mode:

```cpp
Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Player", false);
entity->AddComponent(Phoenix::SpriteComponent("player.png"));
entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
```

If you need to wrap the entities logic in custom classes, you can set the application to the Wrapped mode. In this mode you are responsible for the memory management, update and deletion of the entities.
Here is an example of how to create a simple entity with a sprite component and transform component in Wrapped mode with a Player class:

```cpp

Player::Player(glm::vec2 position, glm::vec2 size)
{
    m_name = "Player";
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->BindOnStart(PX_BIND_EVENT_FN(OnStart));
}

void Player::OnStart()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->RegisterEntityForSerialization(m_name, this);
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_name, false);
    entity->AddComponent(Phoenix::SpriteComponent("player.png"));
    entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
    entity->SetScale(glm::vec2(10, 10));
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
}

void Player::Update()
{
    glm::vec3 transform = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_name)->GetTransformPosition();
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_name)->SetTransformPosition(glm::vec3(transform.x + 0.01, transform.y, transform.z));
}

Player::~Player()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_name)->Destroy();
}

void Player::Serialize(Phoenix::BlobSerializer& serializer)
{
    auto typeId = Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->GetSerializableType(m_name);
    serializer.WriteHeader(typeId);
    serializer.WriteString(m_name);
    serializer.Write(&m_position, sizeof(m_position));
}

void Player::Deserialize(Phoenix::BlobSerializer& serializer)
{
    serializer.ReadString(m_name);
    serializer.Read(&m_position, sizeof(m_position));
}

```
Be aware that you need to register the class for serialization in the constructor and implement the Serialize and Deserialize methods if you want to save and load the entities.
Moreover the two modes are not made to be used together, you need to choose one of them. So in Standalone mode you can't create entities with custom classes and in Wrapped mode you can't create that are not wrapped in a class.

## Game example

The Engine comes with a simple game example proof of concept that demonstrates the engine's capabilities. The game is designed to showcase the engine's core features and provide an example of how to create a 2D game using the Phoenix engine.
You will find the game in the `Phoenix/Game` directory.
This basic game is just a dungeon like game where you can move and shoot mobs with the player.

### Features

* You can move and fire with Arrows and Space keys.
* The player has run and shoot animations.
* Mobs spawn randomly in the level in specific interval.
* The player can shoot the mobs and they will die.
* You can save and load the game with the S and L keys.
* Basic editor UI to create entities and components and visualize the entities and components. You can move the camera by pressing M.


<!-- ROADMAP -->
## Roadmap

- [x] Event Dispatcher
- [x] Input Polling
- [x] Input Registrator
- [x] 2D Renderer
- [ ] Physics System alongside collision system
- [ ] Behavior Tree
- [ ] 3D Renderer