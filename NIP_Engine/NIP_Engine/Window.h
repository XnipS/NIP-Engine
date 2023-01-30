#pragma once

#include <NIP_PCH.h>

#include <functional>

#include "./Events/Event.h"
#include "NIP_Engine/Core.h"

namespace NIP_Engine {
struct WindowProps {
  std::string Title;
  unsigned int Width;
  unsigned int Height;

  WindowProps(const std::string& title = "NIP_Engine",
              unsigned int width = 1280, unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
};

class NIP_ENGINE_API Window {
 public:
  using EventCallbackFn = std::function<void(Event&)>;

  virtual ~Window();

  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  static Window* Create(const WindowProps& props = WindowProps());
};

}  // namespace NIP_Engine