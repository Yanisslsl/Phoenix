#pragma once
#include "../../../../../Core/Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "../../HAL/Windows/Core/Window/include/Window.h"

namespace Phoenix
{

	class PHOENIX_API Application
	{
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<WindowHal> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}
