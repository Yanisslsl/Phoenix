﻿#pragma once
#include "Core/Graphics/DataObjects/include/Texture.h"
#include "glad/glad.h"



namespace Phoenix
{
    /** \class OpenGLTexture2D
     *  \brief A class that represents a 2D texture in OpenGL.
     */
    class OpenGLTexture2D: public Texture2D
    {
    public:
        OpenGLTexture2D(const TextureSpecification& specification);
        OpenGLTexture2D(const std::string& path);

        virtual ~OpenGLTexture2D();

        virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }
        virtual uint32_t GetWidth() const override { return m_Width;  }

        virtual uint32_t GetHeight() const override { return m_Height; }
        virtual uint32_t GetRendererID() const override { return m_RendererID; }

        virtual void SetData(void* data, uint32_t size) override;
        virtual const std::string& GetPath() const override { return m_Path; }

        virtual void Bind(uint32_t slot = 0) const override;
        virtual bool IsLoaded() const override { return m_IsLoaded; }
    private:
        TextureSpecification m_Specification;
        std::string m_Path;
        bool m_IsLoaded = false;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };
}
