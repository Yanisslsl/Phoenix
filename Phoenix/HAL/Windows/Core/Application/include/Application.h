#pragma once
#include "../../Core.h"

namespace Phoenix
{
	class PHOENIX_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();	
}