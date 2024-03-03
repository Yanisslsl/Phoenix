#include "../include/EditorLayer.h"
#include "imgui.h"
#include "Windows/Core/Application/include/Application.h"
#include <GLFW/glfw3.h>

#include "imgui_internal.h"
#include "Events/EventDispatcher.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "../../Utils/KeyCode.h"
#include "Common/Core/Input/include/Input.h"
#include "Editor/include/ImGuiOpenGL.h"
#include "Utils/Timer.h"

namespace Phoenix
{
    EditorLayer::EditorLayer()
        : Layer("EditorLayer")
    {
    }
    void EditorLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());
        
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        static bool show = true;
        DrawEditor();
        // ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        UpdateCameraPosition();
    }

    void EditorLayer::UpdateCameraPosition()
    {
        auto dt = Timer::GetDeltaTime();
        auto camera = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera();
        if(Input::IsKeyPressed(Key::A))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x - ( 1 * dt), camera.GetPosition().y, 1));
        }
        if(Input::IsKeyPressed(Key::D))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x + ( 1 * dt), camera.GetPosition().y, 1));
        }
        if(Input::IsKeyPressed(Key::W))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + ( 1 * dt), 1));
        }
        if(Input::IsKeyPressed(Key::S))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - ( 1 * dt), 1));
        }
    }

    void EditorLayer::DrawEditor()
    {
        if(ImGui::Begin("Editor"))
        {
            if (ImGui::CollapsingHeader("Scene"))
            {
                ImGui::SeparatorText("SCENE EDITOR");
                DrawSceneEditor();
            }
        }
        ImGui::End();
    }

    // init entites tree rendering
    void EditorLayer::DrawSceneEditor()
    {
        if (ImGui::TreeNode("Camera"))
        {
            // @TODO add uid for camera
            if (ImGui::TreeNode((void*)(intptr_t)(10000), "Transform Component"))
            {
                auto camera = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera();
                ImGui::SeparatorText("Position");
                ImGui::Text("X: %f", camera.GetPosition().x);
                ImGui::SameLine();
                ImGui::Text("Y: %f", camera.GetPosition().y);
                ImGui::SeparatorText("Rotation");
                ImGui::TreePop();
            }
            
            ImGui::TreePop();
        }
        std::vector<Ref<Entity>> entities = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntities();
        if (ImGui::TreeNode("Entities"))
        {
            for(auto entity : entities)
            {
                if (ImGui::TreeNode((void*)(intptr_t)entity->m_id, entity->GetName().c_str()))
                {
                    // @TODO: change to component id
                    if (ImGui::TreeNode((void*)(intptr_t)(entity->m_id * 100), "Transform Component"))
                    {
                        ImGui::SeparatorText("Position");
                        ImGui::Text("X: %f", entity->GetTransformPosition().x);
                        ImGui::SameLine();
                        ImGui::Text("Y: %f", entity->GetTransformPosition().y);
                        ImGui::SeparatorText("Rotation");
                        ImGui::Text("X: %f", entity->GetRotation());
                        ImGui::SeparatorText("Scale");
                        ImGui::Text("X: %f", entity->GetScale().x);
                        ImGui::SameLine();
                        ImGui::Text("Y: %f", entity->GetScale().y);
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }
        ImGui::TreePop();
        }
    }

    void EditorLayer::OnAttach()
    {
        ImGui::CreateContext();
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
        // io.KeyMap[ImGuiKey_KeyPadEnter] = Key::Enter;
        io.KeyMap[ImGuiKey_A] = Key::A;
        io.KeyMap[ImGuiKey_C] = Key::C;
        io.KeyMap[ImGuiKey_V] = Key::V;
        io.KeyMap[ImGuiKey_X] = Key::X;
        io.KeyMap[ImGuiKey_Y] = Key::Y;
        io.KeyMap[ImGuiKey_Z] = Key::Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void EditorLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseButtonPressedEvent>(PX_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(PX_BIND_EVENT_FN(EditorLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(PX_BIND_EVENT_FN(EditorLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(PX_BIND_EVENT_FN(EditorLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(PX_BIND_EVENT_FN(EditorLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(PX_BIND_EVENT_FN(EditorLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(PX_BIND_EVENT_FN(EditorLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(EditorLayer::OnWindowResizeEvent));
    }

    bool EditorLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool EditorLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool EditorLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool EditorLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false;
    }

    bool EditorLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool EditorLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool EditorLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);

        return false;
    }

    bool EditorLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());

        return false;
    }
	
    void EditorLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    void EditorLayer::OnDetach()
    {
        //ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorLayer::End()
    {

        // ImGuiIO& io = ImGui::GetIO();
        // Application& app = Application::Get();
        // io.DisplaySize = ImVec2((float)app.GetWindow()->GetWidth(), (float)app.GetWindow()->GetHeight());
        //
        // // Rendering
        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        // {
        //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
        //     ImGui::UpdatePlatformWindows();
        //     ImGui::RenderPlatformWindowsDefault();
        //     glfwMakeContextCurrent(backup_current_context);
        // }
    }

    void EditorLayer::SetDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        // Headers
        colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
        // Buttons
        colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    }

    uint32_t EditorLayer::GetActiveWidgetID() const
    {
        return GImGui->ActiveId;
    }

}