cmake_minimum_required(VERSION 3.8)
project(Phoenix VERSION 1.0 LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define configurations similar to Premake
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")


# Find packages
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Stb REQUIRED)

# Phoenix Library source files
file(GLOB_RECURSE PHOENIX_SOURCES 
     "${CMAKE_SOURCE_DIR}/Phoenix/HAL/*.cpp"
     "${CMAKE_SOURCE_DIR}/Phoenix/HAL/*.h"
     "${CMAKE_SOURCE_DIR}/Phoenix/Core/*.cpp"
     "${CMAKE_SOURCE_DIR}/Phoenix/Core/*.h"
     "${CMAKE_SOURCE_DIR}/Phoenix/Phoenix.h"
     "${CMAKE_SOURCE_DIR}/Phoenix/Core/Events/*.h"
)

# Phoenix Library
add_library(Phoenix SHARED ${PHOENIX_SOURCES})

target_include_directories(Phoenix PRIVATE 
    "${CMAKE_SOURCE_DIR}/Phoenix/HAL"
    "${CMAKE_SOURCE_DIR}/Phoenix/Core"
    "${CMAKE_SOURCE_DIR}/Phoenix/vendor/spdlog/include"
)
#find_path(STB_INCLUDE_DIRS "stb_image")
target_link_libraries(Phoenix PRIVATE 
    glm:glm
    glad::glad
    nlohmann_json::nlohmann_json
    imgui::imgui
    glfw
    spdlog::spdlog
)

target_compile_definitions(Phoenix PRIVATE 
    PHOENIX_BUILD_DLL
    PHOENIX_PLATFORM_WINDOWS
    GLFW_INCLUDE_NONE
)


# Game executable source files
file(GLOB_RECURSE GAME_SOURCES 
     "${CMAKE_SOURCE_DIR}/Game/*.h"
     "${CMAKE_SOURCE_DIR}/Game/*.cpp"
)

# Game executable
add_executable(Game ${GAME_SOURCES})

target_include_directories(Game PRIVATE 
    "${CMAKE_SOURCE_DIR}/Phoenix/HAL"
    "${CMAKE_SOURCE_DIR}/Phoenix"
    "${CMAKE_SOURCE_DIR}/Phoenix/vendor/spdlog/include"
)

target_link_libraries(Game PRIVATE 
    Phoenix
    glm:glm
    spdlog::spdlog
    # Add other libraries your game depends on
)

target_compile_definitions(Game PRIVATE 
    PHOENIX_PLATFORM_WINDOWS
)
