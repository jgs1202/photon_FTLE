cmake_minimum_required(VERSION 3.13)
project(ftle_photon)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES (/System/Library/Frameworks)
include_directories(include /usr/local/include/)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories('/usr/loca/include/')

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${boost_INCLUDE_DIRS})
message(STATUS "boost_INCLUDE_DIRS: ${boost_INCLUDE_DIRS}")

add_executable(ftle_photon main.cpp variables.cpp variables.h ftle.cpp geometry.cpp photonSetting.cpp myMath.cpp gpuSetting.cpp photonParticipate.cpp gradient.cpp visResult.cpp)

target_include_directories (ftle_photon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ftle_photon "/System/Library/Frameworks/GLUT.framework" "/System/Library/Frameworks/openGL.framework" ${OpenCL_LIBRARY} ${OpenCV_LIBS})