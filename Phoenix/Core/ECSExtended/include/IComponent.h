#pragma once
#include "Core/Serialization/include/SerializerSubsystem.h"



namespace Phoenix
{
    class PHOENIX_API IComponent: public ISerializable
    {
    public:
        IComponent() = default;
        virtual void Serialize(BlobSerializer& serializer) = 0;
        virtual void Deserialize(BlobSerializer& serializer) = 0;
        virtual bool IsValid() = 0;
    };
}
