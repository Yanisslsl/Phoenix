#pragma once
#include "HAL/Windows/Core/Application/include/Application.h"
#include "Core/Log/include/Log.h"

#ifdef PHOENIX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv)
{
	Phoenix::Log::Init();
	PX_CORE_WARN("Initialized Log!");
	//auto app = Phoenix::CreateApplication();
	//app->Run();
	//delete app;
}

#endif

