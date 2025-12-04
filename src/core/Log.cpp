#include "core/Log.h"
#include <opentelemetry/instrumentation/spdlog/sink.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace SolAR;

std::shared_ptr<spdlog::logger>&  Log::logger(){
        static auto m_instance = initialize_logger();
   return m_instance;
}

SOLARFRAMEWORK_API void Log::add_sink_console() {
#ifndef __ANDROID__
        sink()->add_sink(std::make_shared< spdlog::sinks::stdout_color_sink_mt>());
#else
        sink()->add_sink(std::make_shared< spdlog::sinks::android_sink >());
#endif
}

SOLARFRAMEWORK_API void Log::add_sink_otel() {
    auto otel_sink = std::make_shared<spdlog::sinks::opentelemetry_sink_mt>();
    otel_sink->set_level(spdlog::level::debug);
    sink()->add_sink(otel_sink);
}
