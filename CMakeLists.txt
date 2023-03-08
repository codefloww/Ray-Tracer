cmake_minimum_required(VERSION 3.24)
project(Ray_Tracer)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

set(SOURCES src/main.cpp src/app.cpp src/image.cpp)
set(HEADERS inc/app.hpp inc/image.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
