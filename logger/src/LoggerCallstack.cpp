#include "LoggerCallstack.h"
#include "LoggerManager.h"
#include "LoggerDefs.h"

using namespace Checkers::Logger;


Callstack::Callstack()
  : m_log_level(LOG_LEVEL_NONE)
  , m_line(0)
{
}

Callstack::Callstack(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName)
  : m_log_level(aLogLevel)
  , m_file_name(aFileName)
  , m_line(aLine)
  , m_function_name(aFunctionName)
{
  Manager::instance().message(m_log_level, m_file_name, m_line, m_function_name, "begin");
}

Callstack::~Callstack()
{
  if(m_log_level > LOG_LEVEL_NONE)
    Manager::instance().message(m_log_level, m_file_name, m_line, m_function_name, "end");
}
