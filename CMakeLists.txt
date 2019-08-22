cmake_minimum_required(VERSION 3.13)
project(ftle_photon)

set(CMAKE_CXX_STANDARD 14)

add_executable(ftle_photon main.cpp variables.cpp variables.h ftle.cpp geometry.cpp photonSetting.cpp myMath.cpp)