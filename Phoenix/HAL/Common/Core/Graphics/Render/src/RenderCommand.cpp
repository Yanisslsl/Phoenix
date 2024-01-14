#include "../include/RenderCommand.h"


namespace Phoenix
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
