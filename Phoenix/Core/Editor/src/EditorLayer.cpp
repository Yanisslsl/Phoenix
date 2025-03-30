#include "imgui.h"
#include <GLFW/glfw3.h>
#include"Base/Base.h"
#include "Editor/include/EditorLayer.h"
#include "imgui_internal.h"
#include "Core/Application/include/Application.h"
#include "Events/EventDispatcher.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Utils/Timer.h"
#include "Utils/Color.h"
#include "Core/Input/include/Input.h"
#include "Core/Scene/include/SceneManagerSubSystem.h"
#include "ECSExtended/include/Entity.h"
#include "ECSExtended/include/TransformSubsytem.h"
#include "ImGuiContextProvider/include/ImGuiOpenGL.h"

namespace Phoenix
{
    EditorLayer::EditorLayer(bool isEnabled)
        : Layer("EditorLayer")
    {
        m_IsEnabled = isEnabled;
    }
    void EditorLayer::OnUpdate()
    {
        if(!m_IsEnabled) return;
        Begin();
        DrawEditor();
        End();
        HandleCameraMovement();
    }


    void EditorLayer::UpdateCameraPosition()
    {
        if(!m_isCameraDevMode) return;
        auto cameraMode = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera().GetCameraMode();
        if(cameraMode == CameraMode::ORTHOGRAPHIC)
        {
            UpdateCamera2DPosition();
        }
        else
        {
            UpdateCamera3DPosition();
        }
    }

    void EditorLayer::UpdateCamera2DPosition()
    {
        auto dt = Timer::GetDeltaTime();
        auto camera = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera();
        if(Input::IsKeyPressed(Key::A))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x - ( m_CameraSpeed * dt), camera.GetPosition().y, 0));
        }
        if(Input::IsKeyPressed(Key::D))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x + ( m_CameraSpeed * dt), camera.GetPosition().y, 0));
        }
        if(Input::IsKeyPressed(Key::W))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + ( m_CameraSpeed * dt), 0));
        }
        if(Input::IsKeyPressed(Key::S))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - ( m_CameraSpeed * dt), 0));
        }
    }

    void EditorLayer::RotateCamera()
    {
        auto cameraPos = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera().GetPosition();
        float mouseXOffset = Input::GetMouseX() - m_LastMouseX;
        float mouseYOffset = m_LastMouseY - Input::GetMouseY();
        m_LastMouseX = Input::GetMouseX();
        m_LastMouseY = Input::GetMouseY();
        mouseXOffset *= m_CameraSensitivity;
        mouseYOffset *= m_CameraSensitivity;
        m_Yaw += mouseXOffset;
        m_Pitch += mouseYOffset;

        if(m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if(m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction = glm::normalize(direction);
        m_CameraDirection = direction;
        Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->LookAt(cameraPos + direction);
    }

    void EditorLayer::HandleCameraMovement()
    {
        UpdateCameraPosition();
        
        if(m_isCameraDevMode)
        {
            if(Input::IsMouseButtonPressed(Mouse::ButtonRight) || Input::IsKeyPressed(Key::Space))
            {
                m_SleepTime += Timer::GetDeltaTime() * 10;
                if(m_SleepTime > 0.3)
                {
                    RotateCamera();
                }
            } else
            {
                m_SleepTime = 0;
                m_LastMouseX = Input::GetMouseX();
                m_LastMouseY = Input::GetMouseY();
            }
        }
    }

    void EditorLayer::UpdateCamera3DPosition()
    {
        auto dt = Timer::GetDeltaTime();
        auto cameraPos = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera().GetPosition();

        if(Input::IsKeyPressed(Key::W))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->LookAt(cameraPos + m_CameraDirection * m_CameraSpeed * dt);
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(cameraPos + m_CameraDirection * m_CameraSpeed * dt);
        }
        else if(Input::IsKeyPressed(Key::S))
        {
            // keep looking forward and move backward
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->LookAt(cameraPos + m_CameraDirection * m_CameraSpeed * dt);
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(cameraPos - m_CameraDirection * m_CameraSpeed * dt);
        }
        else if(Input::IsKeyPressed(Key::D))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->LookAt(cameraPos + m_CameraDirection * m_CameraSpeed * dt);
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(cameraPos - glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f,  0.0f), m_CameraDirection)) * m_CameraSpeed * dt);
        }
        else if(Input::IsKeyPressed(Key::A))
        {
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->LookAt(cameraPos + m_CameraDirection * m_CameraSpeed * dt);
            Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(cameraPos + glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f,  0.0f), m_CameraDirection)) * m_CameraSpeed * dt);
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

    void EditorLayer::DrawSceneEditor()
    {
        
        if (ImGui::TreeNode("Camera"))
        {
            if (ImGui::TreeNode((void*)(intptr_t)(10000), "Transform Component"))
            {
                auto camera = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera();
                auto cameraLookAt = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCameraLookAt();
                ImGui::SeparatorText("Position");
                ImGui::Text("X: %f", camera.GetPosition().x);
                ImGui::Text("Y: %f", camera.GetPosition().y);
                ImGui::Text("Z: %f", camera.GetPosition().z);
                ImGui::SeparatorText("Settings");
                // ImGui::Checkbox("Enable Camera Development Mode", &m_isCameraDevMode);
                if(m_isCameraDevMode)
                {
                    ImGui::SliderFloat("Camera Sensitivity", &m_CameraSensitivity,0, 10.f);
                    ImGui::SliderFloat("Camera Speed", &m_CameraSpeed,1, 100.f);
                }
                ImGui::TreePop();
            }           
            ImGui::TreePop();
        }
        std::vector<Ref<Entity>> entities = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntities();
        
        if (ImGui::TreeNode("Entities"))
        {
            for(auto entity : entities)
            {
                if (ImGui::TreeNode((void*)(intptr_t)entity->m_EntityHandle, entity->GetName().c_str()))
                {
                    if (ImGui::TreeNode((void*)(intptr_t)(entity->m_EntityHandle), "Transform Component"))
                    {
                        ImGui::SeparatorText("Position");
                        ImGui::Text("X: %f", entity->GetTransformPosition().x);                    
                        ImGui::SameLine();
                        float posx = entity->GetTransformPosition().x;
                        if(ImGui::DragFloat("position x", &posx,1., -100.f,1300.f)) //modify position on x axis
                        {
                            entity->SetTransformPosition(glm::vec3(posx,entity->GetTransformPosition().x, entity->GetTransformPosition().z));
                        }
                        ImGui::Text("Y: %f", entity->GetTransformPosition().y);
                        ImGui::SameLine();
                        float posy = entity->GetTransformPosition().y; //modify position on y axis
                        if (ImGui::DragFloat("position y", &posy, 1., -100.f, 800.f))
                        {
                            entity->SetTransformPosition(glm::vec3(entity->GetTransformPosition().x,posy, entity->GetTransformPosition().z));
                        }
                        ImGui::Text("Z: %f", entity->GetTransformPosition().z);                    
                        ImGui::SameLine();
                        float posZ = entity->GetTransformPosition().z;
                        if(ImGui::DragFloat("position z", &posZ,1., -100.f,1300.f)) //modify position on x axis
                        {
                        entity->SetTransformPosition(glm::vec3(entity->GetTransformPosition().x,entity->GetTransformPosition().y, posZ));
                        }
                        ImGui::SeparatorText("Rotation");
                        ImGui::Text("X: %f", entity->GetRotation());
                        ImGui::SameLine();
                        float rotation = entity->GetRotation(); // modify rotation
                        if (ImGui::DragFloat("rotation", &rotation, 1., 0.,180.))
                        {
                            entity->SetRotation(rotation);
                        }
                        ImGui::SeparatorText("Scale");
                        ImGui::Text("X: %f", entity->GetScale().x);
                        ImGui::SameLine();
                        float scx = entity->GetScale().x; // modify scale on x axis
                        if (ImGui::DragFloat("scale x", &scx, 1., 0.,100000.))
                        {
                            entity->SetScale(glm::vec3(scx, entity->GetScale().y, entity->GetScale().z));
                        }                      
                        ImGui::Text("Y: %f", entity->GetScale().y);
                        ImGui::SameLine();
                        float scy = entity->GetScale().y; // modify scale on y axis
                        if (ImGui::DragFloat("scale y", &scy, 1., 0., 100000.))
                        {
                            entity->SetScale(glm::vec3(entity->GetScale().x,scy, entity->GetScale().z));
                        }
                        ImGui::Text("Z: %f", entity->GetScale().z);
                        ImGui::SameLine();
                        float scz = entity->GetScale().z; // modify scale on z axis
                        if (ImGui::DragFloat("scale z", &scz, 1., 0., 100000.))
                        {
                            entity->SetScale(glm::vec3(entity->GetScale().x,entity->GetScale().y, scz));
                        }
                        ImGui::TreePop();               
                    } 
                    ImGui::TreePop();
                }
            }
        ImGui::TreePop();
        }
        if (ImGui::TreeNode("Entity Creation"))
        {           
            std::string s = std::to_string(m_newentityindex); // new entity's name
            
            if (ImGui::Button("Add") && m_newentity == false)              
            {
                m_newentity = true;
            }
            if (m_newentity == true)
            {    
                ImGui::InputFloat("Position x", &posx, 1., (float).3); 
                ImGui::InputFloat("Position y", &posy, 1., (float).3);
                ImGui::InputFloat("Scale", &scale, 1., (float).3);
                ImGui::InputFloat("Rotation", &rotation, 1., (float).3);          
                ImGui::Text("Select color ");
                const char* items[] = { "Red","Green","Blue","Yellow","Orange","Purple","White","Black","Grey","Brown","Pink","Cyan","Magenta","Lime",
                "Teal","Olive","Maroon","Navy","Aqua","Silver","Gold","Crimson","Indigo","Turquoise","Violet","Lavender","Rose","Tan","Beige","Khaki",
                "Coral","Salmon","Peach","Apricot","Mauve","Lilac","Plum","Lemon","Mint","Jade","Emerald","Forest","Pine","Sky","Azure","Cobalt","Sapphire",
                "Tangerine","Amber","Honey","Sand","Scarlett" }; 
                static int item_selected = 0; 
                ImGui::ListBox("listbox", &item_selected, items, IM_ARRAYSIZE(items), 5);
        
                if (ImGui::Button("Apply")) 
                {
                    m_newentityindex++; 
                    Ref<Entity> newEntity = Application::Get().GetSubSystem<EntitySubsystem>()->CreateEntity(s);
                    const auto colorVec = Colors::GetColorFromMap((ColorCode)item_selected);
                    newEntity->AddComponent(SpriteComponent(colorVec, Quad));
                    newEntity->AddComponent(TransformComponent(glm::vec3(posx, posy, 1.), rotation, glm::vec3(1, 1, 1)));
                    newEntity->SetScale((int)scale);
                    m_newentity = false; // hide the display of settings 
                }
            }     
            ImGui::TreePop();      
        }
    }

    void EditorLayer::OnAttach()
    {
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();
        //
        // ImGuiIO& io = ImGui::GetIO();
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        //
        // io.KeyMap[ImGuiKey_Tab] = Key::Tab;
        // io.KeyMap[ImGuiKey_LeftArrow] = Key::Left;
        // io.KeyMap[ImGuiKey_RightArrow] = Key::Right;
        // io.KeyMap[ImGuiKey_UpArrow] = Key::Up;
        // io.KeyMap[ImGuiKey_DownArrow] = Key::Down;
        // io.KeyMap[ImGuiKey_PageUp] = Key::PageUp;
        // io.KeyMap[ImGuiKey_PageDown] = Key::PageDown;
        // io.KeyMap[ImGuiKey_Home] = Key::Home;
        // io.KeyMap[ImGuiKey_End] = Key::End;
        // io.KeyMap[ImGuiKey_Insert] = Key::Insert;
        // io.KeyMap[ImGuiKey_Delete] = Key::Delete;
        // io.KeyMap[ImGuiKey_Backspace] = Key::Backspace;
        // io.KeyMap[ImGuiKey_Space] = Key::Space;
        // io.KeyMap[ImGuiKey_Enter] = Key::Enter;
        // io.KeyMap[ImGuiKey_Escape] = Key::Escape;
        // io.KeyMap[ImGuiKey_A] = Key::A;
        // io.KeyMap[ImGuiKey_C] = Key::C;
        // io.KeyMap[ImGuiKey_V] = Key::V;
        // io.KeyMap[ImGuiKey_X] = Key::X;
        // io.KeyMap[ImGuiKey_Y] = Key::Y;
        // io.KeyMap[ImGuiKey_Z] = Key::Z;
        //
        // ImGui_ImplOpenGL3_Init("#version 410");
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
        io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());

        return false;
    }

    void EditorLayer::Begin()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow()->GetWidth(), (float)app.GetWindow()->GetHeight());
        
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
