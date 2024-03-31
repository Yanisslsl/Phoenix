#pragma once
#include "Core/Log/include/Log.h"
#include "Core/Application/include/Application.h"

#ifdef PHOENIX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv)
{
	Phoenix::Log::Init();
	auto app = Phoenix::CreateApplication();
	delete app;
}

#endif

	