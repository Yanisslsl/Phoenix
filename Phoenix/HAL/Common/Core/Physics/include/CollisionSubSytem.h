// CollisionSubSytem.h

#pragma once

#include "Core.h"
#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/EntitySubsystem.h"

namespace Phoenix
{
    inline uint32_t MAX_COLLIDERS_BY_NODE = 10;
    enum class PHOENIX_API Divide
    {
        HORIZONTAL,
        VERTICAL
    };
    struct BoxCollider;
    struct PHOENIX_API Node
    {
        Node(glm::vec2 topLeftPosition, float width, float height)
            : topLeftPosition(topLeftPosition), width(width), height(height)
        {
            colliders.reserve(MAX_COLLIDERS_BY_NODE);
        }
        ~Node()
        {
            colliders.clear();
            delete left;
            delete right;
        }
        std::vector<BoxCollider> colliders;
        glm::vec2 topLeftPosition;
        float width;
        float height;
        bool Contains(BoxCollider& collider)
        {
            // if(collider.position.x > topLeftPosition.x &&
            //     collider.position.y > topLeftPosition.y &&
            //     collider.position.x < topLeftPosition.x + width &&
            //     collider.position.y < topLeftPosition.y + height)
            //     return true;
            return false;
        }
        Node* left;
        Node* right;
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
        std::tuple<Node*, Node*> CollisionSubSytem::SetNodes(Node* current, Divide divide);
    
        void PrintBst(Node* node);
        std::vector<BoxCollider> GetColliders(BoxCollider& collider);
        Node* SearchNode(BoxCollider& collider, Node* node, Divide divide);
        void Insert(BoxCollider collider);
        void Update(BoxCollider& collider);
        // void Remove(BoxCollider& collider);
        void Remove(BoxCollider& collider, Node* node);
    private:
        Node* m_Root;
    };
}
