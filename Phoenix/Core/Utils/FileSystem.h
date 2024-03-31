// FileSystem.h

#pragma once
#include <filesystem>


namespace Phoenix
{
    class FileSystem
    {
    public:

        static std::string GetAssetsPath()
        {
            return std::filesystem::current_path().string() + "\\assets\\";
        }
    };
}
