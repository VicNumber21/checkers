#ifndef H_LOGGER_DEF_H
#define H_LOGGER_DEF_H

//Log levels
#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ASSERTION 1
#define LOG_LEVEL_CRITICAL 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_WARNING 4
#define LOG_LEVEL_INFO 5
#define LOG_LEVEL_DEBUG 6
#define LOG_LEVEL_VERY_VERBOSE_DEBUG 7

#ifndef DEBUG_BUILD_LOG_LEVEL
#  define DEBUG_BUILD_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#ifndef RELEASE_BUILD_LOG_LEVEL
#  define RELEASE_BUILD_LOG_LEVEL LOG_LEVEL_NONE
#endif

#ifndef LOG_LEVEL
#  ifdef DEBUG
#    pragma message "DEBUG BUILD"
#    define LOG_LEVEL DEBUG_BUILD_LOG_LEVEL
#  else
#    pragma message "RELEASE BUILD"
#    define LOG_LEVEL RELEASE_BUILD_LOG_LEVEL
#  endif
#endif

#if !(LOG_LEVEL_NONE <= LOG_LEVEL  && LOG_LEVEL <= LOG_LEVEL_VERY_VERBOSE_DEBUG)
#  error "LOG_LEVEL must be between 0 and 7"
#endif


//Helpers
#define LOG_LOCATION_INFO __FILE__,__LINE__,__PRETTY_FUNCTION__

#define BB do {       //Block begin
#define BE ; } while(0) //Block end

#define LOGGER_INSTANCE Checkers::Logger::Manager::instance()

#define IF_LOGGER_ON BB if(LOGGER_INSTANCE.isEnabled()) {
#define ENDIF_LOGGER_ON  ; } BE


//Log macro
#if LOG_LEVEL >= LOG_LEVEL_ASSERTION
#  define log_assert(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_ASSERTION, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_assert(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#if LOG_LEVEL >= LOG_LEVEL_CRITICAL
#  define log_critical(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_CRITICAL, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_critical(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#  define log_error(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_ERROR, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_error(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
#  define log_warning(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_WARNING, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_warning(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#  define log_info(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_INFO, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_info(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#  define log_debug(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_DEBUG, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_debug(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#if LOG_LEVEL >= LOG_LEVEL_VERY_VERBOSE_DEBUG
#  define log_vv_debug(...) IF_LOGGER_ON LOGGER_INSTANCE.message(LOG_LEVEL_VERY_VERBOSE_DEBUG, LOG_LOCATION_INFO, ## __VA_ARGS__) ENDIF_LOGGER_ON
#else
#  define log_vv_debug(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE
#endif

#endif //H_LOGGER_DEF_H
