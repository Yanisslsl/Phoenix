#pragma once
#include "Core.h"

namespace Phoenix
{
    class PHOENIX_API NoiseGenerator
    {
    public:
        virtual float Generate2D(float x, float y) = 0;
        virtual void Noise(int width, int height, const char* filename, int octavesNumber) = 0;
        // virtual float Generate3D(float x, float y, float z) = 0;
        // virtual void SetSeed(unsigned int seed) = 0;
    };
}
