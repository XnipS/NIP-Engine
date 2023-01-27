cmake_minimum_required(VERSION 3.14)

project(NIP_Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NIP_Engine SHARED
  NIP_Engine/Core.h
  NIP_Engine/Application.cpp
  NIP_Engine/Application.h
    NIP_Engine/EntryPoint.h
  Test.cpp
  Test.h
)

target_compile_definitions(NIP_Engine PRIVATE NIP_ENGINE_LIBRARY)
