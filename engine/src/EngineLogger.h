#ifndef H_ENGINE_LOGGER_H
#define H_ENGINE_LOGGER_H

//TODO change it in more stable build
#define DEBUG_BUILD_LOG_LEVEL LOG_LEVEL_VERY_VERBOSE_DEBUG

#include <Logger.h>
#include "Error.h"


#define __LOG_MESSAGE_ENGINE_CATCH(LL, M, THROW) catch(Checkers::Engine::Error &e) \
            { __LOG_MESSAGE_STREAM(LL, M << " Checkers::Engine::Error: " << e.what()); if(THROW) throw; } \
            __LOG_MESSAGE_CATCH(LL, M, THROW)

//Log catch throw
#if (LOG_CATCH_THROW_LOG_LEVEL > LOG_LEVEL_NONE && LOG_CATCH_THROW_LOG_LEVEL <= LOG_LEVEL)
#  define log_engine_catch_throw __LOG_MESSAGE_ENGINE_CATCH(LOG_CATCH_THROW_LOG_LEVEL, "caught ", true)
#else
#  define log_engine_catch_throw catch(...) { throw; }
#endif

//Log catch ignore
#if (LOG_CATCH_IGNORE_LOG_LEVEL > LOG_LEVEL_NONE && LOG_CATCH_IGNORE_LOG_LEVEL <= LOG_LEVEL)
#  define log_engine_catch_ignore __LOG_MESSAGE_ENGINE_CATCH(LOG_CATCH_IGNORE_LOG_LEVEL, "ignore caught ", false)
#else
#  define log_engine_catch_ignore catch(...) {}
#endif

#endif //H_ENGINE_LOGGER_H
