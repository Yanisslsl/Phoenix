#pragma once
#include <entt/entity/registry.hpp>
#include "Application.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "Core/ECSExtended/include/SpriteSubsystem.h"
#include "Core/Graphics/Render/include/Renderer.h"
#include "Core/Input/include/InputActionRegistratorSubSystem.h"
#include "Core/Physics/include/CollisionSubSytem.h"
#include "Core/Scene/include/SceneManagerSubSystem.h"
#include "Core/Serialization/include/SerializerSubsystem.h"
#include "Core/Window/include/Window.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Layers/LayerStack/include/LayerStack.h"


namespace Phoenix
{
	class Layer;
	class TransformSubsytem;
	class AnimationSubsystem;


	/**
     * \brief Error codes that can be set by the application, only critical errors should be set to prevent the application from running
     
     */
	enum class ErrorCode
    {
        NO_ERROR,
		LOADING_ASSET_ERROR,
    };

	/**
     * \brief Application mode
     *		  The engine accepts two modes, standalone and wrapped
     *		  In standalone mode, the entities are managed by the engine and the user just have to interact with the created entities via the engine API
     *		  In wrapped mode, the entities are managed by the user, and he is responsible for creating, destroying, update the entities
     *		  Be aware that the wrapped mode may be more complex to use, but it gives more flexibility to the user by make him able to create his own class of entities
     */
	enum class ApplicationMode
	{
		Standalone,
		Wrapped,
	};


	enum class RenderingMode
	{
		RENDERER_2D,
		RENDERER_3D,
	};

	class PHOENIX_API Application
	{
	public:
		/**
         * \brief Application constructor
         * \param mode 
         */
		Application(ApplicationMode mode, RenderingMode renderingMode = RenderingMode::RENDERER_3D);

		/**
         * \brief Application destructor
         */
		~Application();


		/**
         * \brief Get if the application is running
         * \return bool whether the application is running
         */
		bool IsRunning()
		{
			return m_Running;
		}

		/** 
         * \brief Set the application to running
         */
		void SetIsRunning()
		{
			m_Running = true;
			Run();
		}

		

		/** 
         * \brief Stop the application
         */
		void Stop()
		{
			m_Running = false;
		}

		/** 
         * \brief Get the application mode
         * \return ApplicationMode
         */
		ApplicationMode GetMode()
		{
			return m_Mode;
		}

		/** 
         * \brief Set the application error code, only critical errors should be set to prevent the application from running
         * \param errorCode error code to set 
         */
		void SetErrorCode(ErrorCode errorCode)
        {
            m_ErrorCode = errorCode;
        }

		/** 
         * \brief Get the application error code, 
         * \return ErrorCode
         */
		ErrorCode GetErrorCode()
        {
            return m_ErrorCode;
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

		/** 
		 * \brief Get the registry
		 * \return 
		 */
		entt::registry& GetRegistry()
		{
			return m_Registry;
		}

		/**
		 * \brief Get the renderer
		 * \return 
		 */
		Renderer* GetRenderer()
		{
			return m_Renderer;
		}
		
	private:
		ApplicationMode m_Mode;
		ErrorCode m_ErrorCode = ErrorCode::NO_ERROR;
		RenderingMode m_RenderingMode;
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
		Renderer* m_Renderer;
		entt::registry m_Registry;
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}


template <>
inline Phoenix::EntitySubsystem* Phoenix::Application::GetSubSystem<Phoenix::EntitySubsystem>()
{
	return m_EntityManagerSubsystem;
}
