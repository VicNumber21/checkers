#include "LoggerManager.h"
#include "LoggerDefs.h"

#include <iostream>

using namespace Checkers::Logger;


Manager & Manager::instance()
{
  static Manager logger;
  return logger;
}

Manager::Manager()
  : m_enabled(true)
{
}

Manager::~Manager()
{
  std::cerr << std::endl;
}


bool Manager::isEnabled() const
{
  return m_enabled;
}

std::string Manager::getLogLevelName(int aLogLevel) const
{
  static const char * logLevelNames[LOG_LEVEL_COUNT] = {"ASRT", "CRIT", " ERR", "WARN", "INFO", " DEB", "VDEB"};
  return (aLogLevel > LOG_LEVEL_NONE && aLogLevel <= LOG_LEVEL_VERY_VERBOSE_DEBUG ? logLevelNames[aLogLevel - 1]: "?LL?");
}

bool Manager::message(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aMessage)
{
  std::cerr << std::endl;
  std::cerr << getLogLevelName(aLogLevel) << ": ";
  std::cerr << " at " << aFileName << " in " << aLine;
  std::cerr << " from " << aFunctionName;
  std::cerr << ": " << aMessage;

  return true;
}

const char * Manager::value(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aValueSource, const char *aValue)
{
  static std::string cache;

  cache = std::string(aValue);

  std::stringstream ss;
  ss << aValueSource << " = " << cache;
  message(aLogLevel, aFileName, aLine, aFunctionName, ss.str());

  return cache.c_str();
}

bool Manager::value(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aValueSource, bool aValue)
{
  std::stringstream ss;
  ss << aValueSource << " = " << std::boolalpha << aValue;
  message(aLogLevel, aFileName, aLine, aFunctionName, ss.str());

  return aValue;
}
