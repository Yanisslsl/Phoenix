#pragma once

#ifdef PHOENIX_PLATFORM_WINDOWS
	#ifdef PHOENIX_BUILD_DLL
		#define PHOENIX_API __declspec(dllexport)
	#else
		#define PHOENIX_API __declspec(dllimport)
	#endif
#else
	#error Phoenix only supports Windows!
#endif
