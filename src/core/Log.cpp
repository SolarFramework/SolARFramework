#include "core/Log.h"

using namespace SolAR;

std::shared_ptr<spdlog::logger>&  Log::logger(){
        static auto m_instance = initialize_logger();
   return m_instance;
}

