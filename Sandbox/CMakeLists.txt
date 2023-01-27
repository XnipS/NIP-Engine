INCLUDE_DIRECTORIES(
    ../NIP_Engine
)

add_executable(Sandbox Sandbox.cpp)
target_link_libraries(Sandbox NIP_Engine)

install(TARGETS Sandbox
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
