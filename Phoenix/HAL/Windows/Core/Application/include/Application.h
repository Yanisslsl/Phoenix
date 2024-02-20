#pragma once
#include "../../../../../Core/Core.h"
#include "Common/Core/Window/include/Window.h"
#include "../../../../../Core/Layers/LayerStack/include/LayerStack.h"
#include "../../../../../Core/Events/WindowEvent.h"
#include "Common/Core/Input/include/InputActionRegistrator.h"
#include "Common/Core/Scene/include/Scene.h"


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
		WindowHal* GetWindow() { return  m_Window.get(); }
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		EntityManagerOld* GetEntityManager() { return m_EntityManager; }
		static Application& Get() { return *s_Instance; }
	protected:
		// unqique ptr => une seule instance // si je veux passer cette instance il faut la move ce qui change l'ownership // ce qui veut dire que je ne peux pas la copier
		// c'est juste un pointeur dans une classe // quand la classe est detruite le pointeur est detruit
		std::unique_ptr<WindowHal> m_Window;
		static Application* s_Instance;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Layer* m_ImGuiLayer;
		EntityManagerOld* m_EntityManager;
		InputActionRegistrator* m_InputActionRegistrator;

		//@TODO: Add Scene Manager and renderer here 
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}
