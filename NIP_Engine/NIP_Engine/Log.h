#pragma once
#include "../vendor/spdlog/include/spdlog/spdlog.h"
#include "Core.h"

namespace NIP_Engine {
class NIP_ENGINE_API Log {
 public:
  static void Init();
  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
}  // namespace NIP_Engine
// Core logging macros
#define NE_CORE_ERROR(...) \
  ::NIP_Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NE_CORE_WARN(...) ::NIP_Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NE_CORE_INFO(...) ::NIP_Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NE_CORE_TRACE(...) \
  ::NIP_Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NE_CORE_NE_CRITICAL(...) \
  ::NIP_Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define NE_ERROR(...) ::NIP_Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define NE_WARN(...) ::NIP_Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NE_INFO(...) ::NIP_Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define NE_TRACE(...) ::NIP_Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NE_CRITICAL(...) \
  ::NIP_Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
