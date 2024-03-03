#pragma once
#include "Application.h"
#include "../../../../../Core/Core.h"
#include "Common/Core/Window/include/Window.h"
#include "../../../../../Core/Layers/LayerStack/include/LayerStack.h"
#include "../../../../../Core/Events/WindowEvent.h"
#include "Common/Core/ECSExtended/include/EntitySubsystem.h"
#include "Common/Core/Input/include/InputActionRegistratorSubSystem.h"
#include "Common/Core/Scene/include/Scene.h"
#include "Common/Core/Scene/include/SceneManagerSubSystem.h"


namespace Phoenix
{
	// @TODO : find why we need to forward declare WindowResizeEvent and WindowCloseEvent
	class Layer;

	class PHOENIX_API Application
	{
	public:
		Application();
		~Application();

		/**
		 * \brief Run the application
		 */
		void Run();

		/**
		 * \brief Main OnEvent listener that receives all events and dispatches them to appropriate specific event listeners
		 * \param e 
		 */
		void OnEvent(Event& e);

		/**
		 * \brief OnWindowClose event listener
		 * \param e 
		 * \return 
		 */
		bool OnWindowClose(WindowCloseEvent& e);

		/**
		 * \brief OnWindowResize event listener
		 * \param e 
		 * \return 
		 */
		bool OnWindowResize(WindowResizeEvent& e);

		/**
		 * \brief return instance of the window
		 * \return window		
		 */
		WindowHal* GetWindow() { return  m_Window.get(); }

		/**
		 * \brief Push a layer to the layer stack
		 *        Be aware that the layers are updated in the order they are pushed
		 *        @TODO: Add a way to change the order of the layers
		 * \param layer 
		 */
		void PushLayer(Layer* layer);

		/**
		 * \brief Push an overlay to the layer stack
		 *        An overlay is a layer that is updated after all the layers
		 * \param overlay 
		 */
		void PushOverlay(Layer* overlay);

		/**
		 * \brief Returns the application instance, main entry point for getting the application instance
		 * \return 
		 */
		static Application& Get() { return *s_Instance; }

		/**
		 * \brief Returns the application subsystem
		 * \tparam T 
		 * \param subsystem 
		 * \return 
		 */
		template <typename T>
		T* GetSubSystem()
		{
			static_assert(sizeof(T) == 0, "Subsytem not found");
		}

		template <>
		EntitySubsystem* GetSubSystem<EntitySubsystem>()
		{
			return m_EntityManagerSubsystem;
		}

		template <>
		InputActionRegistratorSubSystem* GetSubSystem<InputActionRegistratorSubSystem>()
		{
			return m_InputActionRegistratorSubsystem;
		}

		template <>
		SceneManagerSubSystem* GetSubSystem<SceneManagerSubSystem>()
		{
			return m_SceneManagerSubSystem;
		}

		
	private:
		// unqique ptr => une seule instance // si je veux passer cette instance il faut la move ce qui change l'ownership // ce qui veut dire que je ne peux pas la copier
		// c'est juste un pointeur dans une classe // quand la classe est detruite le pointeur est detruit
		std::unique_ptr<WindowHal> m_Window;
		static Application* s_Instance;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Layer* m_Editor_Layer;
		InputActionRegistratorSubSystem* m_InputActionRegistratorSubsystem;
		EntitySubsystem* m_EntityManagerSubsystem;
		SceneManagerSubSystem* m_SceneManagerSubSystem;
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}
