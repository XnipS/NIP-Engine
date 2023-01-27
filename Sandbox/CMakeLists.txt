cmake_minimum_required(VERSION 3.5)

project(Sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Sandbox Application.cpp)
target_link_libraries(Sandbox NIP_Engine)

install(TARGETS Sandbox
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
