#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace NIP_Engine {
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run() {
	NE_TRACE("BAlls");
	WindowResizeEvent e(1280, 720);

	if (e.IsInCategory(EventCategoryApplication))
	{
	    NE_TRACE(e.ToString());
	}
	if (e.IsInCategory(EventCategoryInput))
	{
	    NE_ERROR(e.ToString());
	}
	while (true) {
	    //printf("NIP_Engine ONLINE");
	}
    }
}
