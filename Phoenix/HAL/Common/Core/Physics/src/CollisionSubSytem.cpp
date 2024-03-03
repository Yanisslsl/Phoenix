#include "../include/CollisionSubSytem.h"

#include <iostream>
#include <queue>
#include <tuple>

#include "Windows/Core/Application/include/Application.h"


namespace Phoenix
{

    float MIN_COLLIDER_DIMENSION = 50;
    uint32_t MAX_DEPTH = 5;
    CollisionSubSytem::CollisionSubSytem()
    {
        auto windowHeight = Application::Get().GetWindow()->GetHeight();
        auto windowWidth = Application::Get().GetWindow()->GetWidth();
        m_Root = new Node(glm::vec2(0, 0), windowWidth, windowHeight);
        Init(m_Root, Divide::VERTICAL);
        PrintBst(m_Root);
    }
    
    CollisionSubSytem::~CollisionSubSytem()
    {
        delete m_Root;
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
            current->left = new Node(current->topLeftPosition, current->width/2.f, current->height);
            current->right = new Node(glm::vec2(current->topLeftPosition.x + current->width /2., current->topLeftPosition.y), current->width / 2.f, current->height);
        } else
        {
            current->left = new Node(current->topLeftPosition, current->width, current->height /2.);
            current->right = new Node(glm::vec2(current->topLeftPosition.x, current->topLeftPosition.y + current->height /2.), current->width, current->height / 2.f);
        }
        return std::make_tuple(current->left, current->right);
    }
    
    void CollisionSubSytem::PrintBst(Node* node)
    {
    }
    
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
        } else
        {
            if(colliderPosition.y > node->right->topLeftPosition.y)
            {
                return SearchNode(collider, node->right, newDivide);
            } 
            return SearchNode(collider, node->left, newDivide);
        }
    }

    void CollisionSubSytem::Insert(BoxCollider& collider)
    {
        auto node = SearchNode(collider, m_Root, Divide::VERTICAL);
        node->colliders.push_back(&collider);
    }
    
    void CollisionSubSytem::Remove(BoxCollider& collider)
    {
        auto node = SearchNode(collider, m_Root,Divide::VERTICAL);
        auto it = std::find(node->colliders.begin(), node->colliders.end(), &collider);
        if(it != node->colliders.end())
        {
            node->colliders.erase(it);
        }
    }
    
    std::vector<BoxCollider*> CollisionSubSytem::GetColliders(BoxCollider& collider)
    {
        auto node = SearchNode(collider, m_Root, Divide::VERTICAL);
        return node->colliders;
    }
}
