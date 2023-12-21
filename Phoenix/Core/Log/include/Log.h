#pragma once
#include <memory>
#include "../../Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Phoenix
{
	class PHOENIX_API Log
	{
	public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};	
}


// Define in separate file
#define PX_CORE_TRACE(...)	::Phoenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_CORE_WARN(...)	::Phoenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_CORE_INFO(...)	::Phoenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PX_CORE_ERROR(...)	::Phoenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PX_CORE_FATAL(...)	::Phoenix::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define PX_TRACE(...)	::Phoenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_WARN(...)	::Phoenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_INFO(...)	::Phoenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PX_ERROR(...)	::Phoenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PX_FATAL(...)	::Phoenix::Log::GetCoreLogger()->fatal(__VA_ARGS__)

