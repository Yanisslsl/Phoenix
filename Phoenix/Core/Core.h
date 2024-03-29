#pragma once
// Macros for use by Phoenix applications
#ifdef PHOENIX_PLATFORM_WINDOWS
	#ifdef PHOENIX_BUILD_DLL
		#define PHOENIX_API __declspec(dllexport)
	#else
		#define PHOENIX_API __declspec(dllimport)
	#endif
#else
	#error Phoenix only supports Windows!
#endif



#ifdef PH_DEBUG
	#define PH_ENABLE_ASSERTS
#endif
