// Timer.h
#pragma once
#include <chrono>

#include "../../../Core/Core.h"


namespace Phoenix
{
    class PHOENIX_API Timer
    {
    public:
        /**
         * \brief Start the timer
         */
        static void Reset()
        {
            m_StartTime = std::chrono::high_resolution_clock::now();
        }

        /**
         * \brief Get the time since the timer started in nanoseconds
         * \return  
         */
        static float Elapsed()
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_StartTime).count() * 0.001f * 0.001f * 0.001f;
        }

        /**
         * \brief Get the time since the timer started in milliseconds
         * \return float
         */
        static float ElapsedMillis()
        {
            return Elapsed() * 1000.0f;
        }

        /**
         * \brief Get the time between the last frame and the current frame in milliseconds
         * \return float
         */
        static float GetDeltaTime()
        {
            float deltaTime =  std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_DeltaTime).count() * 0.001f * 0.001f * 0.001f;
            m_DeltaTime  = std::chrono::high_resolution_clock::now();
            return deltaTime * 1000;
        }

    private:
        inline static std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
        inline static std::chrono::time_point<std::chrono::steady_clock> m_DeltaTime;
    };
}
