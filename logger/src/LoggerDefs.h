#ifndef H_LOGGER_DEF_H
#define H_LOGGER_DEF_H

#include <assert.h>

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

#ifndef DEBUG_BUILD_LOG_VALUE_LOG_LEVEL
#  define DEBUG_BUILD_LOG_VALUE_LOG_LEVEL LOG_LEVEL_VERY_VERBOSE_DEBUG
#endif

#ifndef RELEASE_BUILD_LOG_VALUE_LOG_LEVEL
#  define RELEASE_BUILD_LOG_VALUE_LOG_LEVEL LOG_LEVEL_NONE
#endif

#ifndef LOG_LEVEL
#  ifdef DEBUG
#    pragma message "DEBUG BUILD"
#    define LOG_LEVEL DEBUG_BUILD_LOG_LEVEL
#    define LOG_VALUE_LOG_LEVEL DEBUG_BUILD_LOG_VALUE_LOG_LEVEL
#  else
#    pragma message "RELEASE BUILD"
#    define LOG_LEVEL RELEASE_BUILD_LOG_LEVEL
#    define LOG_VALUE_LOG_LEVEL RELEASE_BUILD_LOG_VALUE_LOG_LEVEL
#  endif
#endif

#if !(LOG_LEVEL_NONE <= LOG_LEVEL  && LOG_LEVEL <= LOG_LEVEL_VERY_VERBOSE_DEBUG)
#  error "LOG_LEVEL must be between 0 and 7"
#endif

#if !(LOG_LEVEL_NONE <= LOG_VALUE_LOG_LEVEL  && LOG_VALUE_LOG_LEVEL <= LOG_LEVEL_VERY_VERBOSE_DEBUG)
#  error "LOG_VALUE_LOG_LEVEL must be between 0 and 7"
#endif


//Helpers
#define LOG_LOCATION_INFO __FILE__,__LINE__,__PRETTY_FUNCTION__

#define BB do {       //Block begin
#define BE ; } while(0) //Block end

#define LOGGER_INSTANCE Checkers::Logger::Manager::instance()

#define LOGGER_ON LOGGER_INSTANCE.isEnabled()

#define IF_LOGGER_ON_BB BB if(LOGGER_ON) {
#define IF_LOGGER_ON_BE  ; } BE

#define __LOG_MESSAGE(LL,...) IF_LOGGER_ON_BB LOGGER_INSTANCE.message(LL, LOG_LOCATION_INFO, ## __VA_ARGS__) IF_LOGGER_ON_BE
#define __NO_LOG_MESSAGE(...) BB (void)sizeof(LOGGER_INSTANCE.message(0, 0, 0, 0, ## __VA_ARGS__)) BE


//Log macro
#if LOG_LEVEL >= LOG_LEVEL_ASSERTION
#  define log_assert(COND)  BB if(!COND) { __LOG_MESSAGE(LOG_LEVEL_ASSERTION, #COND); assert(COND); } BE 
#else
#  define log_assert(COND) assert(COND)
#endif

#if LOG_LEVEL >= LOG_LEVEL_CRITICAL
#  define log_critical(...) __LOG_MESSAGE(LOG_LEVEL_CRITICAL, ## __VA_ARGS__)
#else
#  define log_critical(...) __NO_LOG_MESSAGE(## __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#  define log_error(...) __LOG_MESSAGE(LOG_LEVEL_ERROR, ## __VA_ARGS__)
#else
#  define log_error(...) __NO_LOG_MESSAGE(## __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
#  define log_warning(...) __LOG_MESSAGE(LOG_LEVEL_WARNING, ## __VA_ARGS__)
#else
#  define log_warning(...) __NO_LOG_MESSAGE(## __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#  define log_info(...) __LOG_MESSAGE(LOG_LEVEL_INFO, ## __VA_ARGS__)
#else
#  define log_info(...) __NO_LOG_MESSAGE(## __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#  define log_debug(...) __LOG_MESSAGE(LOG_LEVEL_DEBUG, ## __VA_ARGS__)
#else
#  define log_debug(...) __NO_LOG_MESSAGE(## __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_VERY_VERBOSE_DEBUG
#  define log_vv_debug(...) __LOG_MESSAGE(LOG_LEVEL_VERY_VERBOSE_DEBUG, ## __VA_ARGS__)
#else
#  define log_vv_debug(...) __NO_LOG_MESSAGE(## __VA_ARGS__)
#endif


//Log value
#if (LOG_VALUE_LOG_LEVEL > LOG_LEVEL_NONE && LOG_VALUE_LOG_LEVEL <= LOG_LEVEL)
#  define log_value(X) (LOGGER_ON ? LOGGER_INSTANCE.value(LOG_VALUE_LOG_LEVEL, LOG_LOCATION_INFO, #X, X) : X)
#else
#  define log_value(X) (X)
#endif

#define _lv(X) log_value(X)

#endif //H_LOGGER_DEF_H
