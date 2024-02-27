﻿#include "../include/OpenGLTexture2D.h"
#include "Log/include/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Phoenix
{

    OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification)
    : m_Specification(specification), m_Width(m_Specification.Width), m_Height(m_Specification.Height)
    {
    }
    
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path): m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        char* data = nullptr;
        {
            data = (char*)stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        if(data)
        {
            m_IsLoaded = true;

            m_Width = width;
            m_Height = height;

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4)
            {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            }
            else if (channels == 3)
            {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            m_InternalFormat = internalFormat;
            m_DataFormat = dataFormat;

            PX_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }

    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        uint32_t bpp = m_Specification.Format == ImageFormat::RGBA8 ? 4 : 3;
        PX_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        glBindTextureUnit(slot, m_RendererID);
    }

}
