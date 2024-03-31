#pragma once
#include "HAL/Windows/Core/Application/include/Application.h"
#include "Core/Log/include/Log.h"

#ifdef PHOENIX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv)
{
	Phoenix::Log::Init();
	auto app = Phoenix::CreateApplication();
	delete app;
}

#endif

	