
#include "ImGuiContextProvider/include/ImGuiContextProvider.h"

#include <imgui.h>
#include "Events/KeyEvent.h"
#include "ImGuiContextProvider/include/ImGuiOpenGL.h"

Phoenix::ImGuiContextProvider::ImGuiContextProvider()
{
    m_Context = ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.KeyMap[ImGuiKey_Tab] = Key::Tab;
    io.KeyMap[ImGuiKey_LeftArrow] = Key::Left;
    io.KeyMap[ImGuiKey_RightArrow] = Key::Right;
    io.KeyMap[ImGuiKey_UpArrow] = Key::Up;
    io.KeyMap[ImGuiKey_DownArrow] = Key::Down;
    io.KeyMap[ImGuiKey_PageUp] = Key::PageUp;
    io.KeyMap[ImGuiKey_PageDown] = Key::PageDown;
    io.KeyMap[ImGuiKey_Home] = Key::Home;
    io.KeyMap[ImGuiKey_End] = Key::End;
    io.KeyMap[ImGuiKey_Insert] = Key::Insert;
    io.KeyMap[ImGuiKey_Delete] = Key::Delete;
    io.KeyMap[ImGuiKey_Backspace] = Key::Backspace;
    io.KeyMap[ImGuiKey_Space] = Key::Space;
    io.KeyMap[ImGuiKey_Enter] = Key::Enter;
    io.KeyMap[ImGuiKey_Escape] = Key::Escape;
    io.KeyMap[ImGuiKey_A] = Key::A;
    io.KeyMap[ImGuiKey_C] = Key::C;
    io.KeyMap[ImGuiKey_V] = Key::V;
    io.KeyMap[ImGuiKey_X] = Key::X;
    io.KeyMap[ImGuiKey_Y] = Key::Y;
    io.KeyMap[ImGuiKey_Z] = Key::Z;

    ImGui_ImplOpenGL3_Init("#version 410");
}
