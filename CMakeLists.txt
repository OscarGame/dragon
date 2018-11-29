cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_compile_options(-std=c++11)
project(dragon)

file(GLOB DRAGON_ABSTRACT 			 	"./src/Abstract/*.h" "./src/Abstract/*.cpp")
file(GLOB DRAGON_CAMERA   			    "./src/Camera/*.h" "./src/Camera/*.cpp")
file(GLOB DRAGON_DESCRIPTOR_GEOMETRY 	"./src/Descriptor/Geometry/*.h" "./src/Descriptor/Geometry/*.cpp")

file(GLOB DRAGON_DESCRIPTOR_RADIOMETRT  "./src/Descriptor/Radiometry/*.h" "./src/Descriptor/Radiometry/*.cpp")
file(GLOB DRAGON_INTEGRATOR   			"./src/Integrator/*.h" "./src/Integrator/*.cpp")
file(GLOB DRAGON_LIGHT   			 	"./src/Light/*.h" "./src/Light/*.cpp")

file(GLOB DRAGON_MATH   			    "./src/Math/*.h" "./src/Math/*.cpp")
file(GLOB DRAGON_MATERIAL   			"./src/Material/*.h" "./src/Material/*.cpp")
file(GLOB DRAGON_SYSTEM      			"./src/System/*.h" "./src/System/*.cpp")

file(GLOB DRAGON_SOURCE  			 	"./src/*.h" "./src/*.cpp")
file(GLOB DRAGON_SCENE   			    "./src/Scene/*.h" "./src/Scene/*.cpp")

add_executable(
dragon

${DRAGON_ABSTRACT}
${DRAGON_SOURCE}
${DRAGON_CAMERA}

${DRAGON_LIGHT}
${DRAGON_DESCRIPTOR_RADIOMETRT}
${DRAGON_DESCRIPTOR_GEOMETRY}

${DRAGON_SCENE}
${DRAGON_SYSTEM}
${DRAGON_MATH}

${DRAGON_INTEGRATOR}
${DRAGON_MATERIAL}
)

include_directories("./src/Abstract" "./src/System")
source_group("Abstract" FILES ${DRAGON_ABSTRACT})
source_group("Light" FILES ${DRAGON_LIGHT})
source_group("Camera" FILES ${DRAGON_CAMERA})

source_group("Descriptor\\GEOMETRT" FILES ${DRAGON_DESCRIPTOR_GEOMETRY})
source_group("Descriptor\\RDIOMETRY" FILES ${DRAGON_DESCRIPTOR_RDIOMETRY})
source_group("Scene" FILES ${DRAGON_SCENE})

source_group("System" FILES ${DRAGON_SYSTEM})
source_group("Math" FILES ${DRAGON_MATH})
source_group("Integrator" FILES ${DRAGON_INTEGRATOR})

source_group("Material" FILES ${DRAGON_MATERIAL})

