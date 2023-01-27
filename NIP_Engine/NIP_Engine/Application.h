#pragma once
#include "Core.h"

namespace NIP_Engine {
    class NIP_ENGINE_API Application
    {
	public:
	    Application();
	    virtual ~Application();
	    void Run ();
    };
    // Client definable
    Application* CreateApplication ();
}
