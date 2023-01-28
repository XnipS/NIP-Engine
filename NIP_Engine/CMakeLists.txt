INCLUDE_DIRECTORIES(
    vendor/spdlog/include #Inlcude spdlog (is not a shared library)
)

add_library(NIP_Engine SHARED
    NIP_Engine/Core.h
    NIP_Engine/Log.cpp
    NIP_Engine/Application.cpp
    NIP_Engine/Application.h
    NIP_Engine/EntryPoint.h
    NIP_Engine/Events/Event.h
    NIP_Engine/Events/ApplicationEvent.h
    NIP_Engine/Events/KeyEvent.h
    NIP_Engine/Events/MouseEvent.h
    Test.cpp
    Test.h
)

target_compile_definitions(NIP_Engine PRIVATE NIP_ENGINE_LIBRARY)

target_link_libraries(NIP_Engine spdlog)
