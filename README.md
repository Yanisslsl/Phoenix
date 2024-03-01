# Phoenix
<!-- ABOUT THE PROJECT -->
## About The Project
Welcome to our 2D OpenGL Engine, a comprehensive and lightweight graphics engine developed as a student project. This engine is meticulously crafted using modern C++ and the powerful OpenGL API, aiming to provide an intuitive and efficient platform for creating 2D graphics applications.

The core of this engine is its 2D renderer, designed from the ground up to support a wide range of 2D graphics operations including sprite rendering, animations, text rendering, and basic UI elements. This project serves as a testament to the capabilities of OpenGL in 2D game development and graphical applications, demonstrating how traditional 3D libraries can be adapted for 2D purposes.

<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Installation

1. Install [Cmake](https://cmake.org/download/), and [vcpkg](https://vcpkg.io/en/getting-started)
2. Clone the repo
   ```sh
   git clone https://github.com/Yanisslsl/Phoenix.git
   ```
3. Create the build directory
      ```sh
      mkdir build
      ```
4. From the build directory generate the project with cmake
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=C:/Users/yello/Dev/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
     ```
5. Open the .sln file in the build directory

## Features

### Modern C++ Design:
Utilizes the latest C++17 standards to ensure clean, efficient, and robust code.
### OpenGL-Based Rendering: 
Leverages OpenGL's rendering capabilities to offer high-performance graphics output, tailored for 2D environments.
### Extensible Framework: 
Designed with extensibility in mind, allowing for easy integration of additional features like particle systems, advanced animations, and more.

<!-- ROADMAP -->
## Roadmap

- [x] Event Dispatcher
- [x] Input Polling
- [x] Input Registrator
- [x] 2D Renderer
- [ ] Physics System alongside collision system
- [ ] Behavior Tree
- [ ] ImGui Basic Editor
