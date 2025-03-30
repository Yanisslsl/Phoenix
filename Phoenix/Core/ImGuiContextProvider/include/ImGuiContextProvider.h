#pragma once
#include <imgui_internal.h>

#include "Core.h"
#include "Base/Base.h"

namespace Phoenix
{
    class PHOENIX_API ImGuiContextProvider
    {
    public:
        ImGuiContextProvider();
        ImGuiContext* GetContext() { return m_Context; }

        ~ImGuiContextProvider()
        {
            ImGui::DestroyContext(m_Context);
        }

        // Avoid copying the ImGui context
        ImGuiContextProvider(const ImGuiContextProvider&) = delete;
        ImGuiContextProvider& operator=(const ImGuiContextProvider&) = delete;
    private:
        ImGuiContext* m_Context;
    }; 
}

