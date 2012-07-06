#include "LoggerManager.h"

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

bool Manager::isEnabled() const
{
  return m_enabled;
}

bool Manager::message(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aMessage)
{
  std::cerr << std::endl;
  std::cerr << "LEVEL: " << aLogLevel;
  std::cerr << " at " << aFileName << " in " << aLine;
  std::cerr << " from " << aFunctionName;
  std::cerr << ": " << aMessage;

  return true;
}
