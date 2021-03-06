#ifndef H_LOGGER_MANAGER_H
#define H_LOGGER_MANAGER_H

#include <string>
#include <sstream>


namespace Checkers
{
  namespace Logger
  {
    class Manager
    {
    public:
      static Manager &instance();
      ~Manager();

      bool isEnabled() const;

      bool message(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aMessage = std::string());

      template <class V>
      V value(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aValueSource, const V &aValue)
      {
        std::stringstream ss;
        ss << aValueSource << " = " << aValue;
        message(aLogLevel, aFileName, aLine, aFunctionName, ss.str());

        return aValue;
      }

      const char * value(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aValueSource, const char *aValue);
      bool value(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName, std::string aValueSource, bool aValue);

    private:
      Manager();
      std::string getLogLevelName(int aLogLevel) const;
      std::string reduceFileName(const std::string &aFileName) const;

    private:
      bool m_enabled;
      int m_file_path_level;
    };
  };
};

#endif //H_LOGGER_MANAGER_H
