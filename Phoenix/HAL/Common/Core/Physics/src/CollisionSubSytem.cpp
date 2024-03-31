#include "../include/CollisionSubSytem.h"

#include <iostream>
#include <queue>
#include <tuple>

#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


namespace Phoenix
{

    float MIN_COLLIDER_DIMENSION = 50;
    CollisionSubSytem::CollisionSubSytem()
    {
        auto windowHeight = Application::Get().GetWindow()->GetHeight();
        auto windowWidth = Application::Get().GetWindow()->GetWidth();
        
        m_Root = new Node(glm::vec2(0, 0), windowWidth, windowHeight, UUID::GenerateUUID());
        Init(m_Root, Divide::VERTICAL);
        PrintBst(m_Root);
        m_ColliderSystem = new ColliderSystem(2, 1000);
        m_Nodes_With_Colliders = std::vector<Node*>();
    }
    
    CollisionSubSytem::~CollisionSubSytem()
    {
        delete m_Root;
        delete m_ColliderSystem;
    }

    void CollisionSubSytem::Update()
    {
        for(auto node : m_Nodes_With_Colliders)
        {
            if(node->colliders.size() < 2) continue;
            ChekCollision(node);
        }
    }

    void CollisionSubSytem::ChekCollision(Node* node)
    {
        for(auto& collider : node->colliders)
        {
            for(auto& otherCollider: node->colliders)
            {
                if(collider.m_EntityId == otherCollider.m_EntityId) continue;
                if(collider.CollidesWith(otherCollider))
                {
                    //@TODO: ERROR WHEN TOO MANY COLLIDES
                    // hitCalls defined the number of times the onHit callback will be called
                    // disable this may be a performance bottleneck
                    if(collider.hitCalls < 1)
                    {
                        Ref<Entity> entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(otherCollider.m_EntityId);
                        if (!entity)
                        {
                            PX_WARN("Coundn't call Collider.OnHit because entity is nullptr.");
                            continue;
                        }
                        collider.hitCalls++;
                        if(collider.OnHit != nullptr)
                        {
                            collider.OnHit(entity);
                        }
                    }
                }
            }
        }
    }
    
    void CollisionSubSytem::Init(Node* node, Divide divide)
    {
       if(node->width < MIN_COLLIDER_DIMENSION  || node->height < MIN_COLLIDER_DIMENSION) return ;
        auto s = SetNodes(node, divide);
        auto left = std::get<0>(s);
        auto right = std::get<1>(s);
        if(divide == Divide::VERTICAL)
        {
            Init(left, Divide::HORIZONTAL);
            Init(right, Divide::HORIZONTAL);
        } else
        {
            Init(left, Divide::VERTICAL);
            Init(right, Divide::VERTICAL);
        }
    }
    
    std::tuple<Node*, Node*> CollisionSubSytem::SetNodes(Node* current, Divide divide)
    {
        if (divide == Divide::VERTICAL)
        {
            current->left = new Node(current->topLeftPosition, current->width/2.f, current->height, UUID::GenerateUUID());
            current->right = new Node(glm::vec2(current->topLeftPosition.x + current->width /2., current->topLeftPosition.y), current->width / 2.f, current->height, UUID::GenerateUUID());
        } else
        {
            current->left = new Node(current->topLeftPosition, current->width, current->height /2., UUID::GenerateUUID());
            current->right = new Node(glm::vec2(current->topLeftPosition.x, current->topLeftPosition.y + current->height /2.), current->width, current->height / 2.f, UUID::GenerateUUID());
        }
        return std::make_tuple(current->left, current->right);
    }
    
    void CollisionSubSytem::PrintBst(Node* node)
    {
    }

    void RemoveNode(Node* node)
    {
        if(node->left != nullptr)
        {
            RemoveNode(node->left);
        }
        if(node->right != nullptr)
        {
            RemoveNode(node->right);
        }
        delete node;
    }


    //@TODO ad possibility to get multiples nodes if collider is in multiple nodes
    Node* CollisionSubSytem::SearchNode(BoxCollider& collider, Node* node, Divide divide)
    {
        if(node->width < MIN_COLLIDER_DIMENSION  || node->height < MIN_COLLIDER_DIMENSION)
        {
            return node;
        };
        Divide newDivide;
        if(divide == Divide::VERTICAL)
        {
            newDivide = Divide::HORIZONTAL;
        } else
        {
            newDivide = Divide::VERTICAL;
        }
        const auto colliderPosition = collider.position;
        if(divide == Divide::VERTICAL)
        {
            if(colliderPosition.x < node->right->topLeftPosition.x)
            {
                return SearchNode(collider, node->left, newDivide);
            } 
            
            return SearchNode(collider, node->right, newDivide);
        } 
        if(colliderPosition.y > node->right->topLeftPosition.y)
        {
            return SearchNode(collider, node->right, newDivide);
        } 
        return SearchNode(collider, node->left, newDivide);
    }

    void CollisionSubSytem::AddCollider(EntityId entityId, BoxCollider collider)
    {
        auto node = SearchNode(collider, m_Root, Divide::VERTICAL);
        m_ColliderSystem->AddComponentTo(entityId);
        m_ColliderSystem->SetColliderType(entityId, collider.type);
        m_ColliderSystem->SetColliderHeight(entityId, collider.height);
        m_ColliderSystem->SetColliderWidth(entityId, collider.width);
        m_ColliderSystem->SetColliderPosition(entityId, collider.position);
        m_ColliderSystem->SetOnHitCallback(entityId, collider.OnHit);
        m_ColliderSystem->SetColliderEntity(entityId, entityId);
        m_ColliderSystem->SetColliderHitCalls(entityId, 0);
        m_ColliderSystem->SetColliderNodeId(entityId, node->id);
        collider.m_EntityId = entityId;
        collider.m_Node_Id = node->id;
        Insert(collider);
    }

    void CollisionSubSytem::DeleteCollider(EntityId entityId)
    {
        if(!m_ColliderSystem->HasCollider(entityId)) return;
        auto collider = GetCollider(entityId);
        Remove(collider);
        m_ColliderSystem->DeleteComponent(entityId);
    }

    bool CollisionSubSytem::HasCollider(EntityId entityId)
    {
        auto height = m_ColliderSystem->GetColliderHeight(entityId);
        //@REFACTOR: this is not a good way to check if a collider has been added
        return height != 0;
    }

    BoxCollider CollisionSubSytem::GetCollider(EntityId entityId)
    {
        auto colliderType = m_ColliderSystem->GetColliderType(entityId);
        auto onHitCallback = m_ColliderSystem->GetOnHitCallback(entityId);
        auto position = m_ColliderSystem->GetColliderPosition(entityId);
        auto height = m_ColliderSystem->GetColliderHeight(entityId);
        auto width = m_ColliderSystem->GetColliderWidth(entityId);
        auto _entityId = m_ColliderSystem->GetColliderEntity(entityId);
        auto nodeId = m_ColliderSystem->GetColliderNodeId(entityId);
        auto hitCalls = m_ColliderSystem->GetColliderHitCalls(entityId);
        auto collider = BoxCollider(colliderType, onHitCallback,CollisionShape::RECTANGLE, width, height);
        collider.m_EntityId = _entityId;
        collider.m_Node_Id = nodeId;
        collider.position = position;
        collider.hitCalls = hitCalls;
        return collider;
    }

    // not very efficient, O(n) where n is the number of nodes
    Node* CollisionSubSytem::SearchNode(std::string id)
    {
        auto node = FindNodeById(id, m_Root);
        if(node == nullptr)
        {
            PX_ERROR("Node not found");
            return nullptr;
        }
        return node;
    }

    // @TODO: this function check if a collider needs to change his node and if so, it removes it from the current node and adds it to the new node
    // @REFACTOR: this function is not efficient, due to the fact that all colliders a passed by copy and not by reference
    // so we need to manually updates all the the colliders position in the nodes
    void CollisionSubSytem::Update(EntityId entityId, glm::vec2 position)
    {
        auto collider = GetCollider(entityId);
        // get the node where the collider is
        auto node = SearchNode(collider, m_Root, Divide::VERTICAL);
        // update collider in ECS
        m_ColliderSystem->SetColliderPosition(entityId, position);
        // if the collider is in the same node, we just need to update the position of the collider in the node
        if(node->id == collider.m_Node_Id)
        {
            // updates nodes colliders position
            for(auto& c : node->colliders)
            {
                if(c.m_EntityId == entityId)
                {
                    c.position = position;
                }
            }
            return;
        }
        // remove old collider from the previous node
        Remove(collider);
        // set collider new node id
        m_ColliderSystem->SetColliderNodeId(entityId, node->id);
        // fetch the updated collider
        auto updatedCollider = GetCollider(entityId);
        Insert(updatedCollider);
    }

    void CollisionSubSytem::Insert(BoxCollider collider)
    {
        auto node = SearchNode(collider, m_Root, Divide::VERTICAL);
        collider.m_Node_Id = node->id;
        node->colliders.push_back(collider);
        if(std::find(m_Nodes_With_Colliders.begin(), m_Nodes_With_Colliders.end(), node) != m_Nodes_With_Colliders.end())
        {
            return;
        }
        m_Nodes_With_Colliders.push_back(node);
    }   
    
    Node* CollisionSubSytem::FindNodeById(std::string id, Node* node)
    {
        if(node == nullptr) return nullptr;
        if(node->id == id)
        {
            return node;
        }
        auto left = FindNodeById(id, node->left);
        if(left != nullptr)
        {
            return left;
        }
        auto right = FindNodeById(id, node->right);
        if(right != nullptr)
        {
            return right;
        }
        return nullptr;
    }

    void CollisionSubSytem::Remove(BoxCollider& collider)
    {
        auto node = SearchNode(collider.m_Node_Id);
        if(node == nullptr)
        {
            PX_ERROR("Node not found");
            return;
        }
        auto it = std::find_if(node->colliders.begin(), node->colliders.end(), [&collider](BoxCollider& c){
            return c.m_EntityId == collider.m_EntityId;
        });
        if(it != node->colliders.end())
        {
            node->colliders.erase(it);
        }
        if(node->colliders.size() == 0)
        {
            auto it = std::find_if(m_Nodes_With_Colliders.begin(), m_Nodes_With_Colliders.end(), [&node](Node* n){
                return n->id == node->id;
            });
            if(it != m_Nodes_With_Colliders.end())
            {
                m_Nodes_With_Colliders.erase(it);
            }
        }
    }
    
    std::vector<BoxCollider> CollisionSubSytem::GetColliders(BoxCollider& collider)
    {
        return std::vector<BoxCollider>();
    }
}
