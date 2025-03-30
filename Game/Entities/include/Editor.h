#pragma once
#include "Core/Application/include/Application.h"
#include "Editor/include/EditorLayer.h"
#include "../../Managers/include/BoidManager.h"
class Editor : public Phoenix::EditorLayer
{
public:
    Editor(Phoenix::Ref<BoidManager> boidManager): Phoenix::EditorLayer()
    {
        m_BoidManager = boidManager;
        ImGui::SetCurrentContext(Phoenix::Application::Get().GetImGuiContext()->GetContext());
    }
    float m_Time = 0.0f;
    virtual void OnUpdate() override;
private:
    Phoenix::Ref<BoidManager> m_BoidManager = nullptr;
};
