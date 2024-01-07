#pragma once
#include "../../../../../Core/Core.h"
#include "Common/Core/Window/include/Window.h"
#include "../../../../../Core/Layers/LayerStack/include/LayerStack.h"
#include "../../../../../Core/Events/WindowEvent.h"


namespace Phoenix
{
	// @TODO : find why we need to forward declare WindowResizeEvent and WindowCloseEvent
	class Layer;

	class PHOENIX_API Application
	{
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		std::unique_ptr<WindowHal> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}
