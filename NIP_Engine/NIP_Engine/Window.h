#pragma once

#include <GLFW/glfw3.h>
#include <NIP_PCH.h>

#include <functional>

#include "./Events/Event.h"
#include "NIP_Engine/Core.h"

namespace NIP_Engine {
using EventCallbackFn = std::function<void(Event&)>;
struct WindowData {
  std::string Title;
  unsigned int Width;
  unsigned int Height;
  EventCallbackFn EventCallback;
  bool VSync = false;

  WindowData(const std::string& title = "NIP_Engine", unsigned int width = 1280,
             unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
};

class NIP_ENGINE_API Window {
 public:
  static Window* Create(const WindowData& props = WindowData());
  Window(const WindowData& data);
  virtual ~Window();

  void OnUpdate();

  inline unsigned int GetWidth() const { return m_Data.Width; };
  inline unsigned int GetHeight() const { return m_Data.Height; };

  inline void SetEventCallback(const EventCallbackFn& callback) {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled);
  inline bool IsVSync() const { return m_Data.VSync; };

 private:
  // virtual void Init(const WindowData& data);
  // virtual void Shutdown();
  GLFWwindow* m_Window;
  WindowData m_Data;
};

}  // namespace NIP_Engine