// Timer.h
#pragma once
#include <chrono>

#include "../../../Core/Core.h"


namespace Phoenix
{
    class PHOENIX_API Timer
    {
    public:
        //@TODO move to time class

        static void Reset()
        {
            m_StartTime = std::chrono::high_resolution_clock::now();
        }
	    
        static float Elapsed()
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_StartTime).count() * 0.001f * 0.001f * 0.001f;
        }
	    
        static float ElapsedMillis()
        {
            return Elapsed() * 1000.0f;
        }

    private:
        inline static std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    };
}
