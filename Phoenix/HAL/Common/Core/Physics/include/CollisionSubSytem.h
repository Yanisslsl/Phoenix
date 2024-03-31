// CollisionSubSytem.h

#pragma once

#define UUID_SYSTEM_GENERATOR

#include "Core.h"
#include "Common/Core/ECSExtended/include/EntitySubsystem.h"

namespace Phoenix
{
    class CollisionSubSytem;
    inline uint32_t MAX_COLLIDERS_BY_NODE = 10;
    enum class PHOENIX_API Divide
    {
        HORIZONTAL,
        VERTICAL
    };
    class Node;

    struct ColliderDimensions
    {
        float width;
        float height;
    };

    struct BoxCollider: IComponent, AutoRegister<BoxCollider>
    {
    public:
        BoxCollider() = default;
        BoxCollider(CollisionType type, std::function<void(Ref<Entity>)> onHit, CollisionShape shape, float width, float height, int maxHitCalls = 1)
        : type(type), OnHit(onHit), shape(shape), width(width), height(height), maxHitCalls(maxHitCalls)
        {
            position = glm::vec2(0, 0);
        }
        CollisionType type;
        glm::vec2 position;
        std::function<void(Ref<Entity>)> OnHit = nullptr;
        CollisionShape shape;
        float width;
        float height;
        std::string m_Node_Id = "";
        EntityId m_EntityId;
        int maxHitCalls;
        int hitCalls = 0;

        bool operator==(const BoxCollider& other) const
        {
            return m_EntityId == other.m_EntityId;
        }
      
        //@TODO: create base collider class when adding more colliders types
        bool CollidesWith(BoxCollider other)
        {
            switch (shape)
            {
            case CollisionShape::RECTANGLE:
                {
                    if (other.shape == CollisionShape::RECTANGLE)
                    {
                        if(abs(position.x - other.position.x) > (width + other.width) / 2 ){
                            return false;
                        }
                        if(abs(position.y - other.position.y) > (height + other.height) / 2 ){
                            return false;
                        }
                        return true;
                    }
                }
            default:
                PX_CORE_ASSERT(false, "Collision shape not supported");
            }
        }

        virtual void Serialize(BlobSerializer& serializer) override
        {
            serializer.WriteHeader(BoxColliderComponentSerializeType);
            serializer.Write(&type, sizeof(type));
            serializer.Write(&position, sizeof(position));
            serializer.Write(&shape, sizeof(shape));
            serializer.Write(&width, sizeof(width));
            serializer.Write(&height, sizeof(height));
            serializer.Write(&m_EntityId, sizeof(m_EntityId));
            serializer.Write(&maxHitCalls, sizeof(maxHitCalls));
            serializer.Write(&hitCalls, sizeof(hitCalls));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            serializer.Read(&type, sizeof(type));
            serializer.Read(&position, sizeof(position));
            serializer.Read(&shape, sizeof(shape));
            serializer.Read(&width, sizeof(width));
            serializer.Read(&height, sizeof(height));
            serializer.Read(&m_EntityId, sizeof(m_EntityId));
            serializer.Read(&maxHitCalls, sizeof(maxHitCalls));
            serializer.Read(&hitCalls, sizeof(hitCalls));
        }
    };

    class PHOENIX_API Node
    {
    public:
        Node(glm::vec2 topLeftPosition, float width, float height, std::string id)
            : topLeftPosition(topLeftPosition), width(width), height(height), id(id)
        {
            colliders.reserve(MAX_COLLIDERS_BY_NODE);
        }
        ~Node()
        {
            delete left;
            delete right;
        }
        std::string id;
        std::vector<BoxCollider> colliders;
        glm::vec2 topLeftPosition;
        float width;
        float height;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    class PHOENIX_API CollisionSubSytem
    {
    public:
        CollisionSubSytem();
        ~CollisionSubSytem();
        /**
         * \brief Intializes the CollisionSubSytem
         *        Init the BST
         */
        void Init(Node* node, Divide divide);
        std::tuple<Node*, Node*> SetNodes(Node* current, Divide divide);
    
        void PrintBst(Node* node);
        Node* SearchNode(BoxCollider& collider, Node* node, Divide divide);
        Node* SearchNode(std::string id);
        std::vector<BoxCollider> GetColliders(BoxCollider& collider);
        void Insert(BoxCollider collider);
        void Update(EntityId entityId, glm::vec2 position);
        // void Remove(BoxCollider& collider);
        void Remove(BoxCollider& collider);
        void AddCollider(EntityId entityId, BoxCollider collider);
        void DeleteCollider(EntityId entityId);
        bool HasCollider(EntityId entityId);
        BoxCollider GetCollider(EntityId entityId);
        void ChekCollision(Node* node);
        void Update();
    private:
        std::vector<Node*> m_Nodes_With_Colliders;
        Node* FindNodeById(std::string id, Node* node);
        Node* m_Root;
        ColliderSystem* m_ColliderSystem;
    };
}
