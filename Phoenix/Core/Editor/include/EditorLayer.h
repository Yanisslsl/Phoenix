#include "../../Layers/Layer/include/Layer.h"
#include "../../Events/Event.h"
#include "../../Events/MouseEvent.h"
#include "../../Events/WindowEvent.h"
#include "../../Events/KeyEvent.h"

namespace Phoenix
{
    class PHOENIX_API EditorLayer : public Layer
    {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& e) override;
        virtual void OnUpdate() override;
        void Begin();
        void End();
        void BlockEvents(bool block) { m_BlockEvents = block; }
        void SetDarkThemeColors();
        uint32_t GetActiveWidgetID() const;
    private:
        void DrawEditor();
        void DrawSceneEditor();
        void UpdateCameraPosition();
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
        bool m_BlockEvents = true;
        float m_Time = 0.0f;
    };
}