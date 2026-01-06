#ifndef SOLAR_LOG_H
#define SOLAR_LOG_H

#include <sys/types.h>
#include <sys/stat.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/dist_sink.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ostream_sink.h"
#include <spdlog/sinks/stdout_sinks.h>
#include "SolARFrameworkDefinitions.h"
#include <fstream>
#include <spdlog/fmt/ostr.h>
#include <vector>

#include <opentelemetry/instrumentation/spdlog/sink.h>

// // Un petit wrapper qui capture une référence vers n'importe quel objet
// template <typename T>
// struct Streamable {
//     const T& value;

//     friend std::ostream& operator<<(std::ostream& os, const Streamable& s)
//     {
//         return os << s.value;
//     }

// };

// // Le formatter générique pour le wrapper (Défini UNE SEULE FOIS pour tout le projet)
// template <typename T>
// struct fmt::formatter<Streamable<T>> : fmt::ostream_formatter {};


// // Fonction helper pour déduire le type automatiquement (CTAD)
// template <typename T>
// Streamable<T> as_log(const T& t) { return Streamable<T>{t}; }

namespace SolAR {

/**
 * @class Log
 * @brief <B>Specifies the Log interface class and MACRO's used to manage the logs.</B>
 *
 */

/*! \defgroup MACROS
   *  @{
   */

/*! \addtogroup end_of_process
   * this macro should be used when the process stops
   *  @{
   */

    ///
    /// \brief LOG_RELEASE : flush and release all loggers
    ///

#define LOG_RELEASE \
{ \
    Log::logger()->flush(); \
    spdlog::drop_all();\
}

/*! @} */

/*! \addtogroup Flush_logs
   * this macro should be used when whenever a flsu of logs is required
   *  @{
   */

    ///
    /// \brief LOG_FLUSH : flush all loggers
    ///

#define LOG_FLUSH \
{ \
    Log::logger()->flush(); \
}

/*! @} */

/*! \addtogroup Add_sinks
   * these macros should be used to define console and/or file output streams
   *  @{
   */

    ///
    /// \brief LOG_ADD_LOG_TO_FILE : redirects logs to the specified file
    ///
    /// \details options are : <br>
    /// -LOG_ADD_LOG_TO_FILE(file) : the logs are appended if the file already exists <br>
    /// -LOG_ADD_LOG_TO_FILE(file,"r") : the file is rewinded if it already exists <br>

#define LOG_ADD_LOG_TO_FILE( ... ) { \
    std::vector<const char*> args = { __VA_ARGS__ }; \
    Log::add_sink_file(args);\
}

///
/// \brief LOG_ADD_LOG_TO_CONSOLE : redirects logs to the console
///

#define LOG_ADD_LOG_TO_CONSOLE() \
{ \
    Log::add_sink_console();\
}

#define LOG_ADD_LOG_TO_OTEL() \
{ \
    Log::add_sink_otel();\
}

/*! @} */

/*! \addtogroup Log_styles
   * these macros are to be used in the code
   *  @{
   */

#define LOG_TRACE(fmt, ...) \
{ \
    Log::logger()->trace("[{:5d}] [{}():{}] " fmt,spdlog::details::os::thread_id(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

#define LOG_INFO(fmt, ...) \
{ \
    Log::logger()->info("[{:5d}] [{}():{}] " fmt,spdlog::details::os::thread_id(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

#define LOG_DEBUG(fmt, ...) \
{ \
    Log::logger()->debug("[{:5d}] [{}():{}] " fmt,spdlog::details::os::thread_id(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

#define LOG_CRITICAL(fmt, ...) \
{ \
    Log::logger()->critical("[{:5d}] [{}():{}] " fmt,spdlog::details::os::thread_id(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

#define LOG_WARNING(fmt, ...) \
{ \
    Log::logger()->warn("[{:5d}] [{}():{}] " fmt,spdlog::details::os::thread_id(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

#define LOG_ERROR(fmt, ...) \
{ \
    Log::logger()->error("[{:5d}] [{}():{}] " fmt,spdlog::details::os::thread_id(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

/*! @} */

/*! \addtogroup Log_levels
   * these macros are used to set the log levels
   *
   \details The level priority is defined as follow (in ascending order) : <br>
   debug <br>
   info <br>
   warning <br>
   error <br>
   critical <br>
   trace <br>

   Any level priority reset will enable logs for that level and levels above<br>
   *  @{
   */



#define LOG_SET_DEBUG_LEVEL() \
{ \
    Log::logger()->set_level( spdlog::level::debug ); \
}

#define LOG_SET_CRITICAL_LEVEL() \
{ \
    Log::logger()->set_level( spdlog::level::critical ); \
}

#define LOG_SET_ERROR_LEVEL() \
{ \
    Log::logger()->set_level( spdlog::level::err ); \
}

#define LOG_SET_INFO_LEVEL() \
{ \
    Log::logger()->set_level( spdlog::level::info ); \
}

#define LOG_SET_TRACE_LEVEL() \
{ \
    Log::logger()->set_level( spdlog::level::trace ); \
}

#define LOG_SET_WARNING_LEVEL() \
{ \
    Log::logger()->set_level( spdlog::level::warn ); \
}

/*! @} */

class  Log{


    static std::shared_ptr< spdlog::sinks::dist_sink_st > initialize_sink(){
       auto sinks = std::make_shared< spdlog::sinks::dist_sink_st >();
       return sinks;
     }

    static std::shared_ptr< spdlog::sinks::dist_sink_st >& sink(){
       static auto sink_ptr = initialize_sink();
       return sink_ptr;
     }

    static std::shared_ptr<spdlog::logger> initialize_logger(){

      auto instance = std::make_shared<spdlog::logger>("Logs",sink());
      instance->set_pattern( "[%Y-%m-%d %H:%M:%S:%f] [%l] %v" );
      #ifndef NDEBUG
           instance->set_level( spdlog::level::debug );
      #endif
      return instance;
    }
public:

    static SOLARFRAMEWORK_API std::shared_ptr<spdlog::logger>&  logger();


    static SOLARFRAMEWORK_API void add_sink_file( std::vector<const char*>& args ){
        if(!args.size()){
            LOG_WARNING( "no parameters provided to add_sink_file");
            return;
        }
        auto fileName=std::string(args[0]);
        std::string mode=std::string(" ");
        if(args.size()==2)
           mode=std::string(args[1]);

        size_t found=fileName.find_last_of("/\\");
        std::string pathname;
        struct stat info;

        if(found!=std::string::npos){
        // test if the target directory exists
            pathname=fileName.substr(0,found);
            if( stat( pathname.c_str(), &info ) != 0 ){
                  LOG_WARNING( "{} doesn't exist", pathname.c_str() );
                  return;
            }
       }
       if( info.st_mode & S_IFDIR ){

           // test if the target log file is accessible for writing
            std::ofstream ofs(fileName.c_str(), std::ios_base::app);
            if (!ofs.is_open()) {
              LOG_WARNING( "couldn't acces to {} for writing", fileName.c_str() );
              return;
            }
            ofs.close();

            // test if the target log file is to be reseted
            if(mode=="r")
            {
                if(remove(fileName.c_str())!=0){
                    LOG_WARNING( "couldn't reset {}", fileName.c_str() );}
                 else
                    LOG_INFO( "{} is open and has been rewinded", fileName.c_str() );
            }
            else
                LOG_INFO( "{} is open ", fileName.c_str() );

            sink()->add_sink( std::make_shared< spdlog::sinks::basic_file_sink_st >( fileName.c_str() ) );
        }
        else{
              LOG_WARNING( "{} is not a directory\n", pathname.c_str() );
              return;
        }

    }

    static SOLARFRAMEWORK_API void add_sink_console();

    static SOLARFRAMEWORK_API void add_sink_otel();
};

}
#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON


#endif // SOLAR_LOG_H
