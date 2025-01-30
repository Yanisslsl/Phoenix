    #include "Maths/Noise/include/PerlinNoise.h"

    #include <cmath>
    #include <vector>
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include "stb_image_write.h"

    namespace Phoenix
    {
        float PerlinNoise::Generate2D(float x, float y)
        {
            // grid cells coordinates
            // top left
            int x0 = int(x);
            int y0 = int(y);

            // bottom right
            int x1 = x0 + 1;
            int y1 = y0 + 1;

            // interpolation weights
            float sx = x - (float)x0;
            float sy = y - (float)y0;

            // Compute and interpolate top two corners
            float n0 = GenerateGradientDistanceDotProduct(x0, y0, x, y);
            float n1 = GenerateGradientDistanceDotProduct(x1, y0, x, y);
            float ix0 = CubicInterploation(n0, n1, sx);


            n0 = GenerateGradientDistanceDotProduct(x0, y1, x, y);
            n1 = GenerateGradientDistanceDotProduct(x1, y1, x, y);
            float ix1 = CubicInterploation(n0, n1, sx);

            float value = CubicInterploation(ix0, ix1, sy);

            return value;
        }

        void PerlinNoise::Noise(int width, int height, const char* filename)
        {
            std::vector<unsigned char> pixels(width * height);
            for(int y = 0; y < height; y++)
            {
                for(int x = 0; x < width; x++)
                {

                    float val = 0.0f;
                    float frequency = 1.0f;
                    float amplitude = 1.0f;
                    const int GRID_SIZE = 100.0f;

                    for(int i = 0; i < 12; i++)
                    {
                        val += Generate2D(x * frequency / GRID_SIZE, y * frequency / GRID_SIZE) * amplitude;
                        frequency *= 2.0f;
                        amplitude *= 0.5f;
                    }

                    val *= 1.2f;

                    if(val > 1.0f)
                        val = 1.0f;
                    else if(val < -1.0f)
                        val = -1.0f;
                    
                    pixels[y * width + x] = static_cast<unsigned char>((val + 1.0f) * 127.5f);
                }
            }
            stbi_write_png(filename, width, height, 1, pixels.data(), width);
        }

        float PerlinNoise::GenerateGradientDistanceDotProduct(int ix, int iy, float x, float y)
        {
            // Get gradient from integer coordinates
            glm::vec2 gradient = GenerateRandomGradient(ix, iy);
            // Compute the distance vector
            float dx = x - (float)ix;
            float dy = y - (float)iy;
     
            // Compute the dot-product
            return (dx * gradient.x + dy * gradient.y);
        }


        //@TODO: TO UNDERSTAND
        glm::vec2 PerlinNoise::GenerateRandomGradient(int x, int y)
        {
            // No precomputed gradients mean this works for any number of grid coordinates
            const unsigned w = 8 * sizeof(unsigned);
            const unsigned s = w / 2; 
            unsigned a = x, b = y;
            a *= 3284157443;
     
            b ^= a << s | a >> w - s;
            b *= 1911520717;
     
            a ^= b << s | b >> w - s;
            a *= 2048419325;
            float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
        
            // Create the vector from the angle
            glm::vec2 v;
            v.x = sin(random);
            v.y = cos(random);
     
            return v;
        }

        float PerlinNoise::CubicInterploation(float a0, float a1, float w)
        {
            return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
        }

        // float PerlinNoise::Generate3D(float x, float y, float z)
        // {
        // }
    }
