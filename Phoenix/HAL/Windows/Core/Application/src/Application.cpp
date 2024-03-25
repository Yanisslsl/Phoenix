#include "Windows/Core/Application/include/Application.h"

#include <cstdio>

#include "Editor/include/EditorLayer.h"
#include "Events/EventDispatcher.h"
#include "Utils/Timer.h"
#include "Common/Core/ECSExtended/include/TransformSubsytem.h"


namespace Phoenix
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		m_Window = WindowHal::Create(WindowProps("Phoenix Engine", 1280, 720));
		m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));
		s_Instance = this;
		m_InputActionRegistratorSubsystem = new InputActionRegistratorSubSystem();
		m_EntityManagerSubsystem = new EntitySubsystem();
		m_SceneManagerSubSystem = new SceneManagerSubSystem();
		m_CollisionSubSystem = new CollisionSubSytem();
		m_TransformSubSystem = new TransformSubsytem();
		Renderer::Init();
#ifdef PX_DEBUG
		m_Editor_Layer = new EditorLayer();
		PushOverlay(m_Editor_Layer);
#endif
	}
	
	Application::~Application()	{	}
	void Application::Run()
	{
		while (m_Running)
		{
			Timer::Reset();
			// Update layers first then overlays 
			for(Layer* layer: m_LayerStack.m_Layers)
				layer->OnUpdate();
			for(Layer* layer : m_LayerStack.m_Overlays)
				layer->OnUpdate();
			m_Window->OnUpdate();
			// @TODO: turn this into a layer
			m_CollisionSubSystem->Update();
			m_EntityManagerSubsystem->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		// @TODO: turn this into a layer
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
