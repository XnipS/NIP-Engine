# Infomation
cmake_minimum_required(VERSION 3.5)
project(Population LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Build Engine then Sandbox
add_subdirectory("NIP_Engine")
add_subdirectory("Sandbox")

