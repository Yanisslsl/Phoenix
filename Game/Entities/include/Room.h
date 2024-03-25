// Room.h

#pragma once
#include <string>
#include <glm/vec2.hpp>
#include "Base/Base.h"
#include "Common/Core/Serialization/include/SerializerSubsystem.h"
#include "HAL/Common/Core/ECSExtended/include/Entity.h"


class Room: public Phoenix::ISerializable, public Phoenix::AutoRegister<Room>
{
public:
    Room(glm::vec2 position, glm::vec2 size);
   
    ~Room();
    void Update();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    std::string m_name;
    void Serialize(Phoenix::BlobSerializer& serializer) override;
    void Deserialize(Phoenix::BlobSerializer& serializer) override;
    std::string GetStaticType() override { return "Room"; }
    glm::vec2 m_position;
    int x = 0;
    int y = 0;
    static std::unique_ptr<ISerializable> Create(glm::vec2 position, glm::vec2 size) {
        return std::make_unique<Room>(glm::vec2(0, 0), glm::vec2(100, 100));
    }
    // Room()
    // {
    //     Register("Room", Create);
    // }
};
