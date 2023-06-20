# Real-time concurrent CPU ray tracer

## Aim

This project is aimed to create a real-time ray tracer program on the CPU, utilizing the wide possibilities for parallelization.
Blinn-Phong reflection model is used as a backbone of lighting effects.
Ray-objects intersection testing is conducted using the Möller–Trumbore algorithm for triangles and simple linear algebra operations for plains, spheres, and ellipses.
Global and local view concepts are introduced to implement the 3D object sizing, rotation, and positioning.
To reproduce the properties of the camera, such as field of view and perspective, the camera obscura model is used.

## Prerequisites

Cmake, C++ std lib, SDL2, TBB, GLM

We use SDL2 library as an API for computer multimedia hardware.
Intel Threading Building Blocks is used to utilize the parallelization.
OpenGL Mathematics (GLM) provides a mathematical backbone for our application. 

## Compilation

Just through CMake.

### Usage

To start the program type, for example:

    cd ./cmake-build-release
    ./Ray_Tracer.exe

### Gallery

![img.png](images/Many_Spheres.png)

![img_1.png](images/Complex_Scene_1.png)

![img_2.png](images/Suzanne.png)
