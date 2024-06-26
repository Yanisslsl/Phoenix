#pragma once
#include "Renderer.h"


namespace Phoenix
{
    class PHOENIX_API Renderer3D: public Renderer
    {
    public:
        Renderer3D() = default;
     
        void CreateQuad(std::string name,  const ColorType color, const glm::mat4 modelMat);
    };
}
