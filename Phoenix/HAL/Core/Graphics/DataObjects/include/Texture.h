// Texture.h

#pragma once
#include <cstdint>
#include <string>

#include "../../../Core/Core.h"
#include "../../../Core/Base/Base.h"

namespace Phoenix
{
    /** @brief Enum class for ImageFormat */
    enum class ImageFormat
    {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        RGBA32F
    };
    /** @brief Struct for TextureSpecification */
    struct TextureSpecification
    {
        uint32_t Width = 1;
        uint32_t Height = 1;
        ImageFormat Format = ImageFormat::RGBA8;
        bool GenerateMips = true;
    };

    /** @brief Class for Texture, should be extended in platform specific code  */
    class PHOENIX_API Texture
    {
    public:
        virtual ~Texture() = default;

        /**
         * \brief Get the specification of the texture
         * \return TextureSpecification
         */
        virtual const TextureSpecification& GetSpecification() const = 0;

        /**
         * \brief Get the width of the texture
         * \return uint32_t
         */
        virtual uint32_t GetWidth() const = 0;

        /**
         * \brief Get the height of the texture
         * \return uint32_t
         */
        virtual uint32_t GetHeight() const = 0;

        /**
         * \brief Get the renderer id of the texture
         * \return uint32_t
         */
        virtual uint32_t GetRendererID() const = 0;

        /**
         * @brief Get the path of the texture
         * \return std::string
         */
        virtual const std::string& GetPath() const = 0;

        /**
         * \brief 
         * \param data 
         * \param size 
         */
        virtual void SetData(void* data, uint32_t size) = 0;

        /**
         * \brief Bind the texture
         * \param slot slot to bind
         */
        virtual void Bind(uint32_t slot = 0) const = 0;

        /**
         * \brief Check if the texture is loaded
         * \return bool
         */
        virtual bool IsLoaded() const = 0;
    };

    /** @brief Class for Texture2D */
    class PHOENIX_API Texture2D : public Texture
    {
    public:
        /**
         * \brief Create a texture with a specification
         * \param specification Specification of the texture
         * \return Ref<Texture2D> Texture2D
         */
        static Ref<Texture2D> Create(const TextureSpecification& specification);
        /**
         * \brief Create a texture with a path
         * \param path Path of the texture
         * \return Ref<Texture2D> Texture2D
         */
        static Ref<Texture2D> Create(const std::string& path);
    };
}
