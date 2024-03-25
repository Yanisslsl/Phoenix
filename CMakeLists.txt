cmake_minimum_required(VERSION 3.8)
project(Phoenix VERSION 1.0 LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set build types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Cutom" FORCE)
message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")
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
# Set output directory for Phoenix library
target_include_directories(Phoenix PRIVATE 
    "${CMAKE_SOURCE_DIR}/Phoenix/HAL"
    "${CMAKE_SOURCE_DIR}/Phoenix/Core"
    "${CMAKE_SOURCE_DIR}/Phoenix/vendor/spdlog/include"
)
# Link Phoenix library to Game executable
target_link_libraries(Phoenix PRIVATE 
    glm::glm
    glad::glad
    nlohmann_json::nlohmann_json
    imgui::imgui
    glfw
    spdlog::spdlog
)

# Game executable source files
file(GLOB_RECURSE GAME_SOURCES 
     "${CMAKE_SOURCE_DIR}/Game/*.h"
     "${CMAKE_SOURCE_DIR}/Game/*.cpp"
      "${CMAKE_SOURCE_DIR}/Game/assets/"
)

# Game executable
add_executable(Game ${GAME_SOURCES})

# Set output directory for Game executable
target_include_directories(Game PRIVATE 
    "${CMAKE_SOURCE_DIR}/Phoenix/HAL"
    "${CMAKE_SOURCE_DIR}/Phoenix"
    "${CMAKE_SOURCE_DIR}/Phoenix/vendor/spdlog/include"
    "${CMAKE_SOURCE_DIR}/Phoenix/Core"
)

# Link Phoenix library to Game executable
target_link_libraries(Game PRIVATE 
    Phoenix
    glm::glm
    spdlog::spdlog
)

# Define macro for each build type
target_compile_definitions(Phoenix PRIVATE
  $<$<CONFIG:Debug>:PHOENIX_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:PHOENIX_PLATFORM_WINDOWS>
  $<$<CONFIG:RelWithDebInfo>:PHOENIX_PLATFORM_WINDOWS>
  $<$<CONFIG:Debug>:PHOENIX_BUILD_DLL>
  $<$<CONFIG:Release>:PHOENIX_BUILD_DLL>
  $<$<CONFIG:RelWithDebInfo>:PHOENIX_BUILD_DLL>
)

# Define Debug Macro for Phoenix library
target_compile_definitions(Phoenix PRIVATE
  $<$<CONFIG:Debug>:PX_DEBUG>
  $<$<CONFIG:RelWithDebInfo>:PX_DEBUG>
) 

# Disable debug symbols for RelWithDebInfo build
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -DNDEBUG") 
        
# Define macro for each build type
target_compile_definitions(Game PRIVATE
  $<$<CONFIG:Debug>:PHOENIX_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:PHOENIX_PLATFORM_WINDOWS> 
  $<$<CONFIG:RelWithDebInfo>:PHOENIX_PLATFORM_WINDOWS>
)

# For exe file
add_custom_command(TARGET Game POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Game/assets/textures $<TARGET_FILE_DIR:Game>/assets/textures)
add_custom_command(TARGET Game POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Phoenix/HAL/Common/Core/Graphics/Shaders $<TARGET_FILE_DIR:Game>/assets/shaders)

# for building in visual studio                      
add_custom_command(TARGET Game POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Game/assets/textures ${CMAKE_BINARY_DIR}/assets/textures)
add_custom_command(TARGET Game POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Phoenix/HAL/Common/Core/Graphics/Shaders ${CMAKE_BINARY_DIR}/assets/shaders)

# Set compiler options for Debug build
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Set compiler options for Release build
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")




