#pragma once
#include <glm/vec2.hpp>

#include "Core.h"
#include "NoiseGenerator.h"

namespace Phoenix {
    class PHOENIX_API PerlinNoise : NoiseGenerator
    {
    public:
        PerlinNoise() = default;
        virtual float Generate2D(float x, float y) override;
        // virtual float Generate3D(float x, float y, float z) override;

        virtual void Noise(int width, int height, const char* filename, int octavesNumber) override;
    private:
        float GenerateGradientDistanceDotProduct(int ix, int iy, float x, float y);

        glm::vec2 GenerateRandomGradient(int x, int y);


        float CubicInterploation(float a0, float a1, float w);
    };
}
