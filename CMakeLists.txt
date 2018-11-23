cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_compile_options(-std=c++11)
project(dragon)

SET(DRAGON_SOURCE
src/main.cpp
)
SET(DRAGON_HEADERS
src/Light/light.h
src/Scene/scene.h
src/3DStructure/object.h
src/Camera/camera.h
src/Math/math.h
src/Math/transform.h
src/3DStructure/primitive.h
src/Integrator/integrator.h
src/Material/material.h
src/System/utility.h
)
add_executable(
dragon
${DRAGON_SOURCE}
${DRAGON_HEADERS}
)
