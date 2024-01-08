#include "../../Layers/Layer/include/Layer.h"
#include "../../Events/Event.h"
#include "../../Events/MouseEvent.h"
#include "../../Events/WindowEvent.h"
#include "../../Events/KeyEvent.h"

namespace Phoenix
{
    class PHOENIX_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& e) override;
        virtual void OnUpdate() override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }

        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
		
        void SetDarkThemeColors();

        uint32_t GetActiveWidgetID() const;
    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;
    };
}
