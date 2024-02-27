// Maths.h

#pragma once

#include "glm/glm.hpp"
namespace Phoenix
{
    class Maths
    {
    public:
        struct Matrix4 {
            float m[4][4];
        };

        struct Matrix3 {
            float m[3][3];
        };
             
        struct Vec4
        {
            float x, y, z, w;
        };
        struct Vec3
        {
            float x, y, z;
        };
        struct Vec2
        {
            float x, y;
        };

        struct Color
        {
            float r, g, b, a;
        };
    };
}
