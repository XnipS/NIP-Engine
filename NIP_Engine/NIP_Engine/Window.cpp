#include "Window.h"

#include "Application.h"
#include "Log.h"
#include "NIP_Engine/Application.h"

namespace NIP_Engine {
static bool s_GLFWInitialised = false;

Window* Window::Create(const WindowData& props) { return new Window(props); }

Window::Window(const WindowData& newData) {
  m_Data.Title = newData.Title;
  m_Data.Width = newData.Width;
  m_Data.Height = newData.Height;

  NE_CORE_INFO("Creating window {0} ({1}, {2})", newData.Title, newData.Width,
               newData.Height);

  if (!s_GLFWInitialised) {
    // TODO glfwTerminate on system shutdown
    int success = glfwInit();
    NE_CORE_ASSERT(success, "Could not initialise GLFW! {0}");

    s_GLFWInitialised = true;
  }

  m_Window = glfwCreateWindow((int)newData.Width, (int)newData.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(false);
};

Window::~Window() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
};

void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
  if (glfwWindowShouldClose(m_Window)) {
    Window::~Window();
  }
};

void Window::SetVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_Data.VSync = enabled;
};

}  // namespace NIP_Engine