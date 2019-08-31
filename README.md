# MinecraftStyleOpenGL

## Setup
- All used libraries are copied and referenced from "dependencies" folder:
   - GLFW v3.3
   - GLEW v2.1.0
   - GLM  v0.9.9.5

- Through Visual Studio Project properties, the above mentioned libraries should be refererenced:
  - C/C++ -> General -> Additional Include Directories:
     - ```$(SolutionDir)\MinecraftStyleOpenGL\Dependencies\glew-2.1.0\include```
     - ```$(SolutionDir)\MinecraftStyleOpenGL\Dependencies\glm-0.9.9.5\glm```
     - ```$(SolutionDir)\MinecraftStyleOpenGL\Dependencies\GLFW_3.3\include```
  - Linker -> General -> Additional Library Directories
     - ```$(SolutionDir)\MinecraftStyleOpenGL\Dependencies\glew-2.1.0\lib\Release\Win32```
     - ```$(SolutionDir)\MinecraftStyleOpenGL\Dependencies\GLFW_3.3\lib-vc2019```
  - Linker -> Input -> Additional Dependencies:
```
openGL32.lib
glfw3.lib
glew32.lib
glu32.lib
```
  - Copy glew32.dll and glfw3.dll to the place that main.cpp is located.
  - and to have a portable application, there is only need for texture folder, in addition of glew32.dll and glfw3.dll in release folder. By then, your application should be working on another computer.

- There is no need to statically reference GLEW.

## Project Structure
- Very much attention has been given to isolate each functionality into a header file.
- There is only one .cpp file in the project that contains the "main" method.

## Project Details
- Compiler: msVC19
- Build Processer: Visual Studio
- Architecture: x86, x64
- Render Pipeline: Shader

## Noise Generator
- [simple fractal noise from Jordan Peck](https://github.com/Auburns/FastNoise).

## Keymaps
- WASD for movement.
- Mouse for eye rotation.
- Hold Shift for speed movement.

## TODO
- Multi shader implementation
- Transparency through shaders
- PNG reader
- Animation on Waterfalls.
- Separation of verg and frag shaders from header files.