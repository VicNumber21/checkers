#ifndef H_LOGGER_CALLSTACK_H
#define H_LOGGER_CALLSTACK_H

#include <string>


namespace Checkers
{
  namespace Logger
  {
    class Callstack
    {
    public:
      Callstack();
      Callstack(int aLogLevel, std::string aFileName, int aLine, std::string aFunctionName);
      ~Callstack();

    private:
      int m_log_level;
      std::string m_file_name;
      int m_line;
      std::string m_function_name;
    };
  };
};

#endif //H_LOGGER_CALLSTACK_H
