cmake_minimum_required(VERSION 3.19.1)

project(Rail)

add_executable(Rail 
main.cpp
Railway.cpp
SimulationR.cpp
SimulationE.cpp
SimulationA.cpp
Station.cpp
Timetable.cpp
Train.cpp
utilityA.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(-Wno-c++11-extensions )

target_compile_features(Rail PUBLIC cxx_constexpr)

set(CMAKE_CXX_FLAGS -O2)
