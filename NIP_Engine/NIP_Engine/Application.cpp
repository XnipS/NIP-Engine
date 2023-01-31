#include "Application.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "NIP_Engine/Window.h"

namespace NIP_Engine {

Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application() {}

void Application::Run() {
  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_Window->OnUpdate();
  }
};

}  // namespace NIP_Engine
