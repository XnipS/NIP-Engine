#include "Log.h"
#include "../vendor/spdlog/include/spdlog/sinks/stdout_color_sinks.h"

namespace NIP_Engine {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


    void Log::Init() {
	spdlog::set_pattern("%^[%T][%n]: %v%$");

	s_CoreLogger = spdlog::stdout_color_mt("NIP_ENGINE");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_ClientLogger = spdlog::stdout_color_mt("SANDBOX");
	s_ClientLogger->set_level(spdlog::level::trace);
    }
}
