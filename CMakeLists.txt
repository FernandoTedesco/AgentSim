cmake_minimum_required(VERSION 4.4.0)

project(GPU_Agents VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GPU_Agents main.cpp
grid.cpp
renderer.cpp)

find_package(SDL3 REQUIRED)

target_link_libraries(GPU_Agents PRIVATE SDL3::SDL3)

