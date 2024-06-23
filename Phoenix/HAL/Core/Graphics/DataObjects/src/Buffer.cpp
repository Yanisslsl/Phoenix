#include "Core/Graphics/DataObjects/include/Buffer.h"

#include "Base/Base.h"
#include "Core/Application/include/Application.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLBuffer.h"
#include "Core/Graphics/Render/include/Renderer.h"


namespace Phoenix
{

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Application::Get().GetRenderer()->GetAPI())
        {
        case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
        }

        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(std::vector<float> vertices)
    {
        switch (Application::Get().GetRenderer()->GetAPI())
        {
        case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices);
        }

        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(std::vector<uint32_t> indices)
    {
        switch (Application::Get().GetRenderer()->GetAPI())
        {
        case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices);
        }

        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
