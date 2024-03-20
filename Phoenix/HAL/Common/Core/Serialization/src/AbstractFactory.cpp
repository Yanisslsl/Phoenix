#include "Common/Core/Serialization/include/AbstractFactory.h"
#include "Common/Core/Animation/include/AnimationSubsystem.h"
#include "Common/Core/Physics/include/CollisionSubSytem.h"
#include "Common/Core/Scene/include/Scene.h"

namespace Phoenix
{
    IComponent* TransformComponentFactory::Create()
    {
        return new TransformComponent();
    }

    IComponent* BoxColliderComponentFactory::Create()
    {
        return new BoxCollider();
    }

    IComponent* SpriteComponentFactory::Create()
    {
        return new SpriteComponent();
    }

    IComponent* AnimatorComponentFactory::Create()
    {
        return new AnimatorComponent();
    }

    ISerializable* EntityFactory::Create()
    {
        return new Entity();
    }

    ISerializable* SceneFactory::Create()
    {
        return new Scene();
    }
}
