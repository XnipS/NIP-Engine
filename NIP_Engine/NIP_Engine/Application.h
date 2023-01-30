#pragma once
#include <memory>

#include "Core.h"
#include "Window.h"

namespace NIP_Engine {
class NIP_ENGINE_API Application {
 public:
  Application();
  virtual ~Application();
  void Run();

 private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};
// Client definable
Application *CreateApplication();
}  // namespace NIP_Engine
