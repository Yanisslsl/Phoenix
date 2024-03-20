#pragma once
#include "Common/Core/ECSExtended/include/TransformSubsytem.h"

namespace Phoenix
{
    class AbstractFactory
    {
    public:
        virtual ISerializable* Create() = 0;
    };
    
    class AbstractComponentFactory
    {
    public:
        virtual IComponent* Create() = 0;
    };

    class TransformComponentFactory : public AbstractComponentFactory
    {
        virtual IComponent* Create() override;
     
    };
    
    class BoxColliderComponentFactory : public AbstractComponentFactory
    {
    public:
        virtual IComponent* Create() override;
    };
    
    class SpriteComponentFactory : public AbstractComponentFactory
    {
    public:
        virtual IComponent* Create() override;
    };
    
    class AnimatorComponentFactory : public AbstractComponentFactory
    {
    public:
        virtual IComponent* Create() override;
    };
    
    class EntityFactory : public AbstractFactory
    {
    public:
        virtual ISerializable* Create() override;
    };

    class SceneFactory : public AbstractFactory
    {
    public:
        virtual ISerializable* Create() override;
    };
}
