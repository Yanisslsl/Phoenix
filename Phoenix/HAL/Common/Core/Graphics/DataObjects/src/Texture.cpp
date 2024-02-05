#include "../include/Texture.h"

#include "Common/Core/Graphics/OpenGLImpl/include/OpenGLTexture2D.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"

namespace Phoenix
{
    Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(specification);
        }
        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
        }
        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
