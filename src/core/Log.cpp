#include "core/Log.h"

using namespace SolAR;

std::shared_ptr<spdlog::logger>&  Log::logger(){
        static auto m_instance = initialize_logger();
   return m_instance;
}

SOLARFRAMEWORK_API void Log::add_sink_console() {
#ifndef __ANDROID__
        sink()->add_sink(std::make_shared< spdlog::sinks::stdout_sink_mt >());
#else
        sink()->add_sink(std::make_shared< spdlog::sinks::android_sink_mt >("SolAR Log"));
#endif
    }
