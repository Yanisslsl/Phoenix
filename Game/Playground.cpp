// // #include <glm/ext/matrix_transform.hpp>
// // #include "Phoenix.h"
// // #include "Entities\include\Knight.h"
// // #include "Entities/include/Mob.h"
// // #include "Entities/include/Room.h"
// // #include "Utils/UUID.h"
// // #include "Core/ECSExtended/include/EntitySubsystem.h"
// // #include "ECSExtended/include/TransformSubsytem.h"
// //
// //
// //
// // class PlaygroundLayer : public Phoenix::Layer
// // {
// // public:
// // 	PlaygroundLayer(Phoenix::Application* app = nullptr)
// // 		: Layer("PlaygroundLayer")
// // 	{
// // 		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->Create3DScene("MainLevel");
// // 	
// // 		Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube", true);
// // 		entity->AddComponent(Phoenix::SpriteComponent("ressources/container.jpg", Phoenix::SpriteType::Cube));
// // 		entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0), 180, glm::vec3(5, 5,5) });
// // 		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
// //
// // 		// Phoenix::Ref<Phoenix::Entity> entity1 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube1", false);
// // 		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
// // 		// entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
// // 		// Phoenix::Ref<Phoenix::Entity> entity2 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube", false);
// // 		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
// // 		// entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
// // 		// Phoenix::Ref<Phoenix::Entity> entity3 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube", false);
// // 		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
// // 		// entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
// // 	}
// //
// // 	~PlaygroundLayer()
// // 	{
// // 	}
// // 	void OnUpdate() override
// // 	{
// // 		Phoenix::Timer::Update();
// // 		Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Cube")->SetRotation(Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Cube")->GetRotation() + 0.1f, glm::vec3(1, 1, 0));
// // 		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
// // 	}
// //
// // 	void OnEvent(Phoenix::Event& event) override
// // 	{
// // 	
// // 	}
// // 	
// // private:
// // 	std::vector<std::string> m_entities = { "Cube-1",  };
// // };
// //
// // class Playground : public Phoenix::Application
// // {
// // public:
// // 	Playground(): Application(Phoenix::ApplicationMode::Wrapped)
// // 	{
// // 		PushLayer(new PlaygroundLayer(this));
// // 		Run();
// // 	}
// //
// // 	~Playground()
// // 	{
// // 		
// // 	}
// // };
// //
// // Phoenix::Application* Phoenix::CreateApplication()
// // {
// // 	return new Playground();
// // }
// //
// //
// //
//
// void PathFinding()
// {
//     auto startPosition = findPositionOfStart();
//     std::list<Node*> openList = std::list<Node*>();
//     std::list<Node*> closedList = std::list<Node*>();
//     Node* startNode = new Node();
//     startNode->position = startPosition;
//     startNode->targetPosition = findPositionOfTarget();  // Add this line
//     openList.emplace_back(startNode);
//
//     while(!openList.empty())
//     {
//         auto leafFNode = std::min_element(openList.begin(), openList.end(),
//         [](const auto& a, const auto& b) {
//             return a->f_Cost < b->f_Cost;
//         });
//         
//         auto current = (*leafFNode);
//         closedList.emplace_back(current);
//         openList.remove(current);
//
//         auto neighbors = getNeighbors(current);
//         for(auto neighbor: neighbors)
//         {
//             // Check obstacles FIRST before any other processing
//             if(neighbor->state == CellState::OBSTACLE)
//             {
//                 delete neighbor;  // Clean up the node
//                 continue;
//             }
//
//             if(neighbor->state == TARGET)
//             {
//                 PX_INFO("Target found");
//                 neighbor->parent = current;
//                 std::vector<Node*> path = getPath(neighbor);
//                 // Visualize path here
//                 for(const auto& pathNode : path)
//                 {
//                     int positionX = pathNode->position.y * 100 + 50;
//                     int positionY = pathNode->position.x * 100 + 50;
//                     
//                     Phoenix::Ref<Phoenix::Entity> pathMarker = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(
//                         "path_" + std::to_string(positionX) + std::to_string(positionY), true);
//                     pathMarker->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::YELLOW, Phoenix::SpriteType::Quad));
//                     pathMarker->AddComponent(Phoenix::TransformComponent{ 
//                         glm::vec3(positionX, positionY, 0.), 
//                         180, 
//                         glm::vec3(30., 30., 1.) 
//                     });
//                 }
//                 return;  // Exit after finding path
//             }
//
//             // Now check if in closed list
//             auto closedListIt = std::find_if(closedList.begin(), closedList.end(), 
//             [neighbor](const Node* node) {
//                 return node->position.x == neighbor->position.x && node->position.y == neighbor->position.y;
//             });
//
//             if(closedListIt != closedList.end())
//             {
//                 delete neighbor;
//                 continue;
//             }
//
//             // Now safe to compute costs
//             neighbor->computeFCost();
//
//             auto openListIt = std::find_if(openList.begin(), openList.end(), 
//             [neighbor](const Node* node) {
//                 return node->position.x == neighbor->position.x && node->position.y == neighbor->position.y;
//             });
//
//             if(openListIt != openList.end() && (*openListIt)->f_Cost < neighbor->f_Cost)
//             {
//                 delete neighbor;
//                 continue;
//             }
//
//             openList.emplace_back(neighbor);
//         }
//     }
// }
