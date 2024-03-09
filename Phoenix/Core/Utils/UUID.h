// UUID.h

#pragma once
#include <random>
#include <sstream>

namespace Phoenix
{
    class UUID
    {
    public:
        inline static std::string GenerateUUID()
        {
            std::random_device rd; // Obtain a random number from hardware
            std::mt19937 eng(rd()); // Seed the generator
            std::uniform_int_distribution<> distr(0, 15); // Define the range

            std::stringstream ss;
            for (int i = 0; i < 8; i++) ss << std::hex << distr(eng); // time_low
            ss << "-";
            for (int i = 0; i < 4; i++) ss << std::hex << distr(eng); // time_mid
            ss << "-4"; // version 4
            for (int i = 0; i < 3; i++) ss << std::hex << distr(eng); // time_hi_and_version
            ss << "-";
            ss << std::hex << (8 + distr(eng) % 4); // variant reserved for future use
            for (int i = 0; i < 3; i++) ss << std::hex << distr(eng); // clock_seq
            ss << "-";
            for (int i = 0; i < 12; i++) ss << std::hex << distr(eng); // node
            return ss.str();
        }
    };
}
