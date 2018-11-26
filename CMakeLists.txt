cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_compile_options(-std=c++11)
project(dragon)

SET(DRAGON_SOURCE
src/main.cpp
)
SET(DRAGON_LIGHT
src/Light/light.h
)
SET(DRAGON_SCENE
src/Scene/scene.h
)
SET(DRAGON_DESCRIPTOR_GEOMETRY
src/Descriptor/Geometry/object.h
src/Descriptor/Geometry/primitive.h
src/Descriptor/Geometry/floor.h
src/Descriptor/Geometry/sphere.h
)
SET(DRAGON_DESCRIPTOR_RADIOMETRT)
SET(DRAGON_DESCRIPTOR
${DRAGON_DESCRIPTOR_GEOMETRY}
${DRAGON_DESCRIPTOR_RADIOMETRT}
)
SET(DRAGON_CAMERA
src/Camera/camera.h
)
SET(DRAGON_MATH
src/Math/math.h
src/Math/transform.h
)
SET(DRAGON_INTEGRATOR
src/Integrator/integrator.h
)
SET(DRAGON_MATERIAL
src/Material/material.h
)
SET(DRAGON_SYSTEM
src/System/utility.h
)
add_executable(
dragon
${DRAGON_SOURCE}
${DRAGON_CAMERA}
${DRAGON_LIGHT}
${DRAGON_DESCRIPTOR}
${DRAGON_SCENE}
${DRAGON_SYSTEM}
${DRAGON_MATH}
${DRAGON_INTEGRATOR}
${DRAGON_MATERIAL}
)
source_group("Light" FILES ${DRAGON_LIGHT})
source_group("Camera" FILES ${DRAGON_CAMERA})
source_group("Descriptor\\GEOMETRT" FILES ${DRAGON_DESCRIPTOR_GEOMETRY})
source_group("Descriptor\\RDIOMETRY" FILES ${DRAGON_DESCRIPTOR_RDIOMETRY})

source_group("Scene" FILES ${DRAGON_SCENE})
source_group("System" FILES ${DRAGON_SYSTEM})
source_group("Math" FILES ${DRAGON_MATH})
source_group("Integrator" FILES ${DRAGON_INTEGRATOR})
source_group("Material" FILES ${DRAGON_MATERIAL})

