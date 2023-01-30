#pragma once
#include "Application.h"
#include "Log.h"
extern NIP_Engine::Application *NIP_Engine::CreateApplication();

int main(int argc, char **argv) {
  NIP_Engine::Log::Init();
  NE_CRITICAL("Core!");
  NE_CORE_INFO("Client!");
  auto app = NIP_Engine::CreateApplication();
  app->Run();
  delete app;
  return 0;
}
