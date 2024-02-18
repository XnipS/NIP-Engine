# Get SDL2 from package manager
find_package(SDL2 REQUIRED)

# Glob files
file(GLOB_RECURSE ENGINE_GLOB
    ./*.cpp
    ./*.h
)

# Compile source code to library
add_library(NIP_Engine SHARED
    ${ENGINE_GLOB}
)

# Link SDL2
target_include_directories(NIP_Engine PRIVATE SDL2)

# Add NIP_Engine as compile library target
#target_compile_definitions(NIP_Engine
#    PRIVATE NIP_ENGINE_LIBRARY
#)
