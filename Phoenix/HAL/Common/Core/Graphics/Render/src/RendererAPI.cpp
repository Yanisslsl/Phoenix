#include "../include/RendererAPI.h"
#include "../../../Core/Log/include/Log.h"
#include "../../Render/include/OpenGLRendererAPI.h"


namespace Phoenix
{
    // Maybe set this with platform detection 
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
        }

        return nullptr;
    }

    
}
