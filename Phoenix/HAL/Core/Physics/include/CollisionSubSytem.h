#pragma once

#define UUID_SYSTEM_GENERATOR

#include <glm/vec2.hpp>

#include "Core.h"
#include "Core/ECSExtended/include/IComponent.h"
#include "Core/Serialization/include/BlobSerializer.h"

namespace Phoenix
{
    class CollisionSubSytem;

    enum class CollisionType
    {
        STATIC,
        DYNAMIC
    };

    enum class CollisionShape
    {
        CIRCLE,
        RECTANGLE
    };

    /**
     * \brief Max colliders allowed by node
     */
    inline uint32_t MAX_COLLIDERS_BY_NODE = 50;

    /**
     * \brief Divide enum
     *        Used to divide the screen
     */
    enum class PHOENIX_API Divide
    {
        HORIZONTAL,
        VERTICAL
    };
    class Node;

    /**
     * \brief BoxCollider owned by an entity used to detect collision
     */
    struct PHOENIX_API BoxCollider: IComponent, AutoRegister<BoxCollider>
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
        std::string m_Node_Id;
        int maxHitCalls;
        int hitCalls = 0;
        EntityIdentifier entityId;

        bool operator==(const BoxCollider& other) const
        {
            // return m_EntityId == other.m_EntityId;
            return true;
        }

        /**
         * \brief Check if the collider collides with another collider
         * \param other BoxCollider to check
         * \return bool
         */
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
                return false;
            }
        }

        virtual void Serialize(BlobSerializer& serializer) override
        {
            // serializer.WriteHeader(BoxColliderComponentSerializeType);
            // serializer.Write(&type, sizeof(type));
            // serializer.Write(&position, sizeof(position));
            // serializer.Write(&shape, sizeof(shape));
            // serializer.Write(&width, sizeof(width));
            // serializer.Write(&height, sizeof(height));
            // serializer.Write(&m_EntityId, sizeof(m_EntityId));
            // serializer.Write(&maxHitCalls, sizeof(maxHitCalls));
            // serializer.Write(&hitCalls, sizeof(hitCalls));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            // serializer.Read(&type, sizeof(type));
            // serializer.Read(&position, sizeof(position));
            // serializer.Read(&shape, sizeof(shape));
            // serializer.Read(&width, sizeof(width));
            // serializer.Read(&height, sizeof(height));
            // serializer.Read(&m_EntityId, sizeof(m_EntityId));
            // serializer.Read(&maxHitCalls, sizeof(maxHitCalls));
            // serializer.Read(&hitCalls, sizeof(hitCalls));
        }

        virtual bool IsValid()
        {
            return false;
        }
    };

    /**
     * \brief Node class
     *        Container of colliders, represents a sub division of the screen
     */
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

    /**
    * \brief Collision SubSystem
    *        Used to manage collision components in the game.
    */
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

        /**
         * \brief Set the nodes of the BST
         * \param current Node to set
         * \param divide Divide to set
         * \return std::tuple<Node*, Node*>
         */
        std::tuple<Node*, Node*> SetNodes(Node* current, Divide divide);

        /**
         * \brief Search for a node in the BST
         * \param collider BoxCollider to search
         * \param node Node to search
         * \param divide Divide to search
         * \return Node*
         */
        Node* SearchNode(BoxCollider& collider, Node* node, Divide divide);

        /**
         * \brief Search for a node in the BST
         * \param id id of the node to search
         * \return Node*
         */
        Node* SearchNode(std::string id);

        /**
         * \brief Find a node by id
         * \param id id of the node to find
         * \param node Node to search
         * \return Node*
         */
        Node* FindNodeById(std::string id, Node* node);

        /**
         * \brief Insert a collider in the correct node
         * \param collider BoxCollider to insert
         */
        void Insert(BoxCollider collider);

        /**
         * \brief Update the position of a collider, and move it to the correct node if needed
         * \param entityId EntityId of the collider
         * \param position position to update
         */
        void Update(EntityIdentifier entityId, glm::vec2 position);

        /**
         * \brief Remove a collider from the BST
         * \param collider BoxCollider to remove
         */
        void Remove(BoxCollider& collider);

        /**
         * \brief Add a collider to the system
         * \param entityId EntityIdentifier of the collider
         * \param collider BoxCollider to add
         */
        void AddCollider(EntityIdentifier entityId, BoxCollider collider);

        /**
         * \brief Delete a collider from the system
         * \param entityId EntityIdentifier of the collider
         */
        void DeleteCollider(EntityIdentifier entityId);

        /**
         * \brief Check if an entity has a collider
         * \param entityId EntityIdentifier to check
         * \return bool
         */
        bool HasCollider(EntityIdentifier entityId);

        /**
         * \brief Get the collider of an entity
         * \param entityId EntityIdentifier to get
         * \return BoxCollider
         */
        BoxCollider GetCollider(EntityIdentifier entityId);

        /**
         * \brief Check collision of a node
         * \param node Node to check
         */
        void ChekCollision(Node* node);

        /**
         * \brief Update the system by checking collisions
         */
        void Update();
    private:
        std::vector<Node*> m_Nodes_With_Colliders;
        Node* m_Root;
        std::vector<BoxCollider> m_Colliders;
    };
}
