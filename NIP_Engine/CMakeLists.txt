# Inlcude spdlog (is not a shared library)
INCLUDE_DIRECTORIES(
    vendor/spdlog/include
)

# Add PCH as seperate library
add_library(NIP_PCH SHARED NIP_PCH.cpp)

# Compile source to library
add_library(NIP_Engine SHARED
    NIP_Engine/Core.h
    NIP_Engine/Log.cpp
    NIP_Engine/Application.cpp NIP_Engine/Application.h
    NIP_Engine/EntryPoint.h
    NIP_Engine/Events/Event.h
    NIP_Engine/Events/ApplicationEvent.h
    NIP_Engine/Events/MouseEvent.h
	NIP_Engine/Events/KeyEvent.h
    Test.cpp Test.h
)

# Mark NIP_PCH library as precompile
target_precompile_headers(NIP_PCH
    PRIVATE NIP_PCH.h
)

# Add NIP_Engine as compile library target
target_compile_definitions(NIP_Engine
    PRIVATE NIP_ENGINE_LIBRARY
)

# TODO test if this is required
target_link_libraries(NIP_Engine spdlog)
