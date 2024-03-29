#include "Windows/Core/Application/include/Application.h"

#include <cstdio>
#include "Events/EventDispatcher.h"
#include "ImGui/include/ImGuiLayer.h"
#include "Utils/Timer.h"


namespace Phoenix
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		Timer::Reset();
		m_Window = WindowHal::Create(WindowProps("Phoenix Engine", 1280, 720));
		m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));
		s_Instance = this;
		m_InputActionRegistratorSubsystem = new InputActionRegistratorSubSystem();
		m_EntityManagerSubsystem = new EntitySubsystem();
		Renderer::Init();
#ifdef PX_DEBUG
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
#endif
	}
	
	Application::~Application()	{	}
	void Application::Run()
	{
		while (m_Running)
		{
			// Update layers first then overlays 
			for(Layer* layer: m_LayerStack.m_Layers)
				layer->OnUpdate();
			for(Layer* layer : m_LayerStack.m_Overlays)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		m_InputActionRegistratorSubsystem->OnEvent(e);
		dispatcher.Dispatch<WindowCloseEvent>(PX_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(Application::OnWindowResize));
		for(Layer* layer: m_LayerStack.m_Overlays)
			layer->OnEvent(e);
		for(Layer* layer: m_LayerStack.m_Layers)
			layer->OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Renderer::Shutdown();
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}
