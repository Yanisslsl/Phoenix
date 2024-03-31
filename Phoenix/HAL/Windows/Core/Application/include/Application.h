#pragma once
#include "Application.h"
#include "../../../../../Core/Core.h"
#include "Common/Core/Window/include/Window.h"
#include "../../../../../Core/Layers/LayerStack/include/LayerStack.h"
#include "../../../../../Core/Events/WindowEvent.h"
#include "Common/Core/Animation/include/AnimationSubsystem.h"
#include "Common/Core/ECSExtended/include/SpriteSubsystem.h"
#include "Common/Core/Input/include/InputActionRegistratorSubSystem.h"
#include "Common/Core/Physics/include/CollisionSubSytem.h"
#include "Common/Core/Scene/include/Scene.h"
#include "Common/Core/Scene/include/SceneManagerSubSystem.h"



namespace Phoenix
{
	class Layer;
	class TransformSubsytem;

	enum class ApplicationMode
	{
		Standalone,
		Wrapped,
	};

	class PHOENIX_API Application
	{
	public:
		Application(ApplicationMode mode);
		~Application();

		bool IsRunning()
		{
			return m_Running;
		}

		void SetIsRunning()
		{
			m_Running = true;
			Run();
		}

		ApplicationMode GetMode()
		{
			return m_Mode;
		}
		/**
		 * \brief Run the application
		 */
		void Run();

		void Update();

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
		InputActionRegistratorSubSystem* Application::GetSubSystem<InputActionRegistratorSubSystem>()
		{
			return m_InputActionRegistratorSubsystem;
		}

		template <>
		SceneManagerSubSystem* Application::GetSubSystem<SceneManagerSubSystem>()
		{
			return m_SceneManagerSubSystem;
		}

		template <>
		CollisionSubSytem* Application::GetSubSystem<CollisionSubSytem>()
		{
			return m_CollisionSubSystem;
		}

		template <>
		TransformSubsytem* Application::GetSubSystem<TransformSubsytem>()
		{
			return m_TransformSubSystem;
		}

		template <>
		AnimationSubsystem* Application::GetSubSystem<AnimationSubsystem>()
		{
			return m_AnimationSubsystem;
		}

		template <>
		SerializerSubsystem* Application::GetSubSystem<SerializerSubsystem>()
		{
			return m_SerializerSubsystem;
		}

		template <>
		SpriteSubsystem* Application::GetSubSystem<SpriteSubsystem>()
		{
			return m_SpriteSubsystem;
		}

	private:
		ApplicationMode m_Mode;

	private:
		std::unique_ptr<WindowHal> m_Window;
		static Application* s_Instance;
		bool m_Running = false;
		LayerStack m_LayerStack;
		Layer* m_Editor_Layer;
		InputActionRegistratorSubSystem* m_InputActionRegistratorSubsystem;
		EntitySubsystem* m_EntityManagerSubsystem;
		SceneManagerSubSystem* m_SceneManagerSubSystem;
		CollisionSubSytem* m_CollisionSubSystem;
		TransformSubsytem* m_TransformSubSystem;
		AnimationSubsystem* m_AnimationSubsystem;
		SerializerSubsystem* m_SerializerSubsystem;
		SpriteSubsystem* m_SpriteSubsystem;
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}


template <>
inline Phoenix::EntitySubsystem* Phoenix::Application::GetSubSystem<Phoenix::EntitySubsystem>()
{
	return m_EntityManagerSubsystem;
}
