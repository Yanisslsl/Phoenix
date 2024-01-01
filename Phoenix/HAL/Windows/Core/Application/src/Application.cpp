#include "../include/Application.h"

#include <cstdio>

#include "Events/EventDispatcher.h"
#include "Log/include/Log.h"

namespace Phoenix
{

	Application::Application()
	{
		m_Window = WindowHal::Create(WindowProps("Phoenix Engine", 1280, 720));
		m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application()	{	}
	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(PX_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(Application::OnWindowResize));
		PX_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}
}
