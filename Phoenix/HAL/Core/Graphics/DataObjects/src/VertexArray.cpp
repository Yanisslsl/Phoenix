

#include "Core/Graphics/DataObjects/include/VertexArray.h"

#include "Core/Application/include/Application.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLVertexArray.h"
#include "Core/Graphics/Render/include/Renderer.h"

namespace Phoenix
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Application::Get().GetRenderer()->GetAPI())
        {
            case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }

        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
