
#include <glm/vec3.hpp>

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"
#include "Layers/Layer/include/Layer.h"

namespace Phoenix
{
    /** 
     * \brief EditorLayer class
     *        Used to create the EditorLayer
     */
    class PHOENIX_API EditorLayer : public Layer
    {
    public:
        /** 
         * \brief EditorLayer constructor
         */
        EditorLayer();

        /** 
         * \brief EditorLayer destructor
         */
        ~EditorLayer() = default;

        /** 
         * \brief OnAttach
         *        Called when the layer is attached
         */
        virtual void OnAttach() override;

        /** 
         * \brief OnDetach
         *        Called when the layer is detached
         */
        virtual void OnDetach() override;

        /** 
         * \brief OnEvent
         *        Called when an event is triggered
         * \param e Event to handle
         */
        virtual void OnEvent(Event& e) override;

        /** 
         * \brief OnUpdate
         *        Called when the layer is updated
         */
        virtual void OnUpdate() override;

        /** 
         * \brief Begin
         *        Called when the layer is started
         */

        /** 
         * \brief Begin
         *        Called when the layer is started
         */
        void Begin();

        /** 
         * \brief End
         *        Called when the layer is ended
         */
        void End();

        /** 
         * \brief BlockEvents
         *        Used to block events
         * \param block bool
         */
        void BlockEvents(bool block) { m_BlockEvents = block; }

        /** 
         * \brief SetDarkThemeColors
         *        Used to set the dark theme colors
         */
        void SetDarkThemeColors();

        /** 
         * \brief GetActiveWidgetID
         *        Used to get the active widget ID
         * \return uint32_t
         */
        uint32_t GetActiveWidgetID() const;
    private:

        /** 
         * \brief DrawEditor
         *        Used to draw the editor
         */
        void DrawEditor();

        /** 
         * \brief DrawSceneEditor
         *        Used to draw the scene editor
         */
        void DrawSceneEditor();

        void UpdateCameraPosition();

         /** 
         * \brief UpdateCameraPosition
         *        Update the camera position
         */
        void UpdateCamera2DPosition();

        void UpdateCamera3DPosition();

        /** 
         * \brief OnMouseButtonPressedEvent
         *        Called when a mouse button is pressed
         */
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);

        /** 
         * \brief OnMouseButtonReleasedEvent
         *        Called when a mouse button is released
         */
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

        /** 
         * \brief OnMouseMovedEvent
         *        Called when the mouse is moved
         */
        bool OnMouseMovedEvent(MouseMovedEvent& e);

        /** 
         * \brief OnMouseScrolledEvent
         *        Called when the mouse is scrolled
         */
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);

        /** 
         * \brief OnKeyPressedEvent
         *        Called when a key is pressed
         */
        bool OnKeyPressedEvent(KeyPressedEvent& e);

        /** 
         * \brief OnKeyReleasedEvent
         *        Called when a key is released
         */
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);

        /** 
         * \brief OnKeyTypedEvent
         *        Called when a key is typed
         */
        bool OnKeyTypedEvent(KeyTypedEvent& e);

        /** 
         * \brief OnWindowResizeEvent
         *        Called when the window is resized
         */
        bool OnWindowResizeEvent(WindowResizeEvent& e);


        /** 
         * \brief RotateCamera
         *        Rotate the camera
         */
        void RotateCamera();
    public:
        /** Editor ECS settings */
        bool m_BlockEvents = true;
        float m_Time = 0.0f;

        bool m_newentity = false;
        int m_newentityindex = 1;
        float posx = 0.;
        float posy = 0.;
        float scale = 0;
        float rotation = 0;

    private:
        /** Camera Settings */
        float m_LastMouseX = 740.0f;
        float m_LastMouseY = 340.0f;
        float m_Yaw = -90.0f;
        float m_Pitch = 0.0f;
        glm::vec3 m_CameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        float m_SleepTime = 0.0f;
        bool m_isCameraDevMode = false;
        float m_CameraSensitivity = 0.1f;
        float m_CameraSpeed = 10.f;
    };
}
