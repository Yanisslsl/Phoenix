#pragma once
#include <map>
#include <glm/vec3.hpp>

#include "../../Core/Core.h"

namespace Phoenix
{
    using ColorCode = uint16_t;

    using ColorType = glm::vec3;


    namespace Color
    {
        PHOENIX_API enum : ColorCode
        {
            RED,
          GREEN,
          BLUE,
          YELLOW,
          ORANGE,
          PURPLE,
          WHITE,
          BLACK,
          GREY,
          BROWN,
          PINK,
          CYAN,
          MAGENTA,
          LIME,
          TEAL,
          OLIVE,
          MAROON,
          NAVY,
          AQUA,
          SILVER,
          GOLD,
          CRIMSON,
          INDIGO,
          TURQUOISE,
          VIOLET,
          LAVENDER,
          ROSE,
          TAN,
          BEIGE,
          KHAKI,
          CORAL,
          SALMON,
          PEACH,
          APRICOT,
          MAUVE,
          LILAC,
          PLUM,
          LEMON,
          MINT,
          JADE,
          EMERALD,
          FOREST,
          PINE,
          SKY,
          AZURE,
          COBALT,
          SAPPHIRE,
          TANGERINE,
          AMBER,
          HONEY,
          SAND,
          SCARLET
        };
        

    }
        class PHOENIX_API Colors
    {
    public:
        inline static glm::vec3 GetColor(ColorCode color)
        {
            auto c = Color::RED;
            return colors[color];
        }
    private:
        inline static std::map<ColorCode, glm::vec3> colors {
  {Color::RED, glm::vec3(1.0f, 0.0f, 0.0f)},
    {Color::GREEN, glm::vec3(0.0f, 1.0f, 0.0f)},
    {Color::BLUE, glm::vec3(0.0f, 0.0f, 1.0f)},
    {Color::YELLOW, glm::vec3(1.0f, 1.0f, 0.0f)},
    {Color::ORANGE, glm::vec3(1.0f, 0.65f, 0.0f)},
    {Color::PURPLE, glm::vec3(0.5f, 0.0f, 0.5f)},
    {Color::WHITE, glm::vec3(1.0f, 1.0f, 1.0f)},
    {Color::BLACK, glm::vec3(0.0f, 0.0f, 0.0f)},
    {Color::GREY, glm::vec3(0.5f, 0.5f, 0.5f)},
    {Color::BROWN, glm::vec3(0.65f, 0.16f, 0.16f)},
    {Color::PINK, glm::vec3(1.0f, 0.75f, 0.8f)},
    {Color::CYAN, glm::vec3(0.0f, 1.0f, 1.0f)},
    {Color::MAGENTA, glm::vec3(1.0f, 0.0f, 1.0f)},
    {Color::LIME, glm::vec3(0.75f, 1.0f, 0.0f)},
    {Color::TEAL, glm::vec3(0.0f, 0.5f, 0.5f)},
    {Color::OLIVE, glm::vec3(0.5f, 0.5f, 0.0f)},
    {Color::MAROON, glm::vec3(0.5f, 0.0f, 0.0f)},
    {Color::NAVY, glm::vec3(0.0f, 0.0f, 0.5f)},
    {Color::AQUA, glm::vec3(0.0f, 1.0f, 1.0f)},
    {Color::SILVER, glm::vec3(0.75f, 0.75f, 0.75f)},
    {Color::GOLD, glm::vec3(1.0f, 0.84f, 0.0f)},
    {Color::CRIMSON, glm::vec3(0.86f, 0.08f, 0.24f)},
    {Color::INDIGO, glm::vec3(0.29f, 0.0f, 0.51f)},
    {Color::TURQUOISE, glm::vec3(0.25f, 0.88f, 0.82f)},
    {Color::VIOLET, glm::vec3(0.93f, 0.51f, 0.93f)},
    {Color::LAVENDER, glm::vec3(0.9f, 0.9f, 0.98f)},
    {Color::ROSE, glm::vec3(1.0f, 0.0f, 0.5f)},
    {Color::TAN, glm::vec3(0.82f, 0.71f, 0.55f)},
    {Color::BEIGE, glm::vec3(0.96f, 0.96f, 0.86f)},
    {Color::KHAKI, glm::vec3(0.94f, 0.9f, 0.55f)},
    {Color::CORAL, glm::vec3(1.0f, 0.5f, 0.31f)},
    {Color::SALMON, glm::vec3(0.98f, 0.5f, 0.45f)},
    {Color::PEACH, glm::vec3(1.0f, 0.89f, 0.71f)},
    {Color::APRICOT, glm::vec3(0.98f, 0.81f, 0.69f)},
    {Color::MAUVE, glm::vec3(0.88f, 0.69f, 1.0f)},
    {Color::LILAC, glm::vec3(0.78f, 0.64f, 0.78f)},
    {Color::PLUM, glm::vec3(0.56f, 0.27f, 0.52f)},
    {Color::LEMON, glm::vec3(1.0f, 1.0f, 0.4f)},
    {Color::MINT, glm::vec3(0.24f, 0.71f, 0.54f)},
    {Color::JADE, glm::vec3(0.0f, 0.66f, 0.42f)},
    {Color::EMERALD, glm::vec3(0.31f, 0.78f, 0.47f)},
    {Color::FOREST, glm::vec3(0.13f, 0.55f, 0.13f)},
    {Color::PINE, glm::vec3(0.1f, 0.49f, 0.47f)},
    {Color::SKY, glm::vec3(0.53f, 0.81f, 0.92f)},
    {Color::AZURE, glm::vec3(0.0f, 0.5f, 1.0f)},
    {Color::COBALT, glm::vec3(0.0f, 0.28f, 0.67f)},
    {Color::SAPPHIRE, glm::vec3(0.06f, 0.32f, 0.73f)},
    {Color::TANGERINE, glm::vec3(1.0f, 0.52f, 0.0f)},
    {Color::AMBER, glm::vec3(1.0f, 0.75f, 0.0f)},
    {Color::HONEY, glm::vec3(1.0f, 0.92f, 0.73f)},
    {Color::SAND, glm::vec3(0.76f, 0.7f, 0.5f)},
    {Color::SCARLET, glm::vec3(1.0f, 0.14f, 0.0f)}
        };
    };
}