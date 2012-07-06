#ifndef H_LOGGER_MANAGER_H
#define H_LOGGER_MANAGER_H

#include <string>


namespace Checkers
{
  namespace Logger
  {
    class Manager
    {
    public:
      static Manager &instance();

      bool isEnabled() const;

      bool message(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aMessage = std::string());

    private:
      Manager();

    private:
      bool m_enabled;
    };
  };
};

#endif //H_LOGGER_MANAGER_H
