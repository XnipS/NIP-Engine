#include "TestWindow.h"

#include <GLFW/glfw3.h>
#include <NIP_PCH.h>

#include "NIP_Engine/Core.h"
#include "NIP_Engine/Log.h"
#include "NIP_Engine/Window.h"

namespace NIP_Engine {
static bool s_GLFWInitialised = false;

Window* Window::Create(const WindowProps& props) {
  return new TestWindow(props);
}

TestWindow::TestWindow(const WindowProps& props) { Init(props); }

TestWindow::~TestWindow() { Shutdown(); }

void TestWindow::Init(const WindowProps& props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  NE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
               props.Height);

  if (!s_GLFWInitialised) {
    // TODO glfwTerminate on system shutdown
    int success = glfwInit();
    NE_CORE_ASSERT(success, "Could not initialise GLFW! {0}");

    s_GLFWInitialised = true;
  }

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(false);
}
void TestWindow::Shutdown() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();  // TODO make sure this is correct
}

void TestWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}
void TestWindow::SetVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_Data.VSync = enabled;
}

bool TestWindow::IsVSync() const { return m_Data.VSync; }
}  // namespace NIP_Engine