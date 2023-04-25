cmake_minimum_required(VERSION 3.24)
project(Ray_Tracer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(Boost REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp src/*/*.cpp src/*.cc main.cpp)
file(GLOB_RECURSE HEADERS inc/*.hpp inc/*.h inc/*/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${BOOST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})

if(WIN32 AND MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC inc)
