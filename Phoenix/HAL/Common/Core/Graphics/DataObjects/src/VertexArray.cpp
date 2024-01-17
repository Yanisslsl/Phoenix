﻿#include "../include/VertexArray.h"

#include "../../Render/include/Renderer.h"
#include "../../OpenGLImpl/include/OpenGLVertexArray.h"

namespace Phoenix
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }

        PX_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
