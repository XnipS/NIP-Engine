#include <NIP_Engine.h>

#include "NIP_Engine/Application.h"

class Sandbox : public NIP_Engine::Application {
 public:
  Sandbox() {}
  ~Sandbox() {}
};

NIP_Engine::Application* NIP_Engine::CreateApplication() {
  return new Sandbox();
}
