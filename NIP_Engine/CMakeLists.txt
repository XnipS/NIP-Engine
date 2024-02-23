# Get SDL2 from package manager
find_package(SDL2 REQUIRED)

# Include SDL2
INCLUDE_DIRECTORIES(
	${SDL2_INCLUDE_DIRS}
)

# Glob files
file(GLOB_RECURSE ENGINE_GLOB
    ./*.cpp
    ./*.h
)

# Compile source code to library
add_library(NIP_Engine SHARED
    ${ENGINE_GLOB}
)

# Link SDL2 and GL
target_link_libraries(NIP_Engine SDL2 SDL2main GL GLEW glfw GLU glut)
# Include SDL
#target_include_directories(NIP_Engine PRIVATE SDL2 SDL2main)

