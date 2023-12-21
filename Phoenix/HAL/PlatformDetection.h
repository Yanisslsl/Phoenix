#pragma once
#pragma once
namespace HAL
{
	class PlatformDetection abstract
	{
	public:
		PlatformDetection() = default;
		~PlatformDetection() = default;
		enum class PlatformType
		{
			Windows,
			Linux,
			MacOS,
			Android,
			iOS,
			Unknown
		};
		struct Platform {
			PlatformType Type = PlatformType::Unknown;
		};
		Platform* GetPlatform();
		void DetectPlatform();

	private:
		Platform* m_Platform;
	};
}


