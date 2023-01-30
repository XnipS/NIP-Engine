#include "Application.h"

#include <memory>

#include "NIP_Engine/Window.h"

namespace NIP_Engine {

Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application() {}

void Application::Run() {
  while (m_Running) {
    m_Window->OnUpdate();
  }
}
}  // namespace NIP_Engine
