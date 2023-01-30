# Inlcude spdlog (is not a shared library)
INCLUDE_DIRECTORIES(
	. # inlcude parent dir
    vendor/spdlog/include # include spdlog
	# TODO include glfw
)

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
#option(NE_USING_PCH "Build NIP-Engine using PCH" ON)
#if(NE_USING_PCH)
	message(STATUS "Adding PCHs")
	target_precompile_headers(NIP_Engine
    	PRIVATE NIP_PCH.h
	)
#else()
#	message(STATUS "PCHs ignored")
#endif()

# Add NIP_Engine as compile library target
target_compile_definitions(NIP_Engine
    PRIVATE NIP_ENGINE_LIBRARY
)
