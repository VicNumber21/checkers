#define DEBUG_BUILD_LOG_LEVEL LOG_LEVEL_VERY_VERBOSE_DEBUG

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TextTestProgressListener.h>

#include <stdexcept>

#include "Logger.h"
#include "MultilineStream.h"

class A
{
};

std::ostream & operator<<(std::ostream &aOut, const A &aA)
{
  log_callstack();
  static int c = 0;
  (void) aA;
  log_vv_debug_s(++c);
  return aOut << "class A";
}

void firstCallFunc()
{
  log_callstack();
}


void printHelp(std::string name)
{
  int lastSlashPos = name.rfind('/');
  name.erase(0, lastSlashPos + 1);
  std::cout << "Usage:" << std::endl;
  std::cout << " " << name << " [-v|-V|] [test-suite|test-name]" << std::endl;
  std::cout << "    -v|-V - verbose mode" << std::endl;
  std::cout << "    test-sute|test-case - \"TestSuiteName1[::TestCase]\"" << std::endl;
  std::cout << " " << name << " -h|-help|--help|help - this help" << std::endl;
}

//TODO write real tests for logger
int
main( int argc, char* argv[] )
{
  log_callstack();

  try
  {
    try
    {
      log_vv_debug_throw(std::bad_exception());
    }
    log_catch_throw
  }
  log_catch_ignore

  log_debug();
  MultilineStream ms1;
  ms1 << "a = " << std::endl;
  ms1 << "b === " << std::endl;
  ms1.makeFrame();
  log_debug_m(ms1);

  log_debug();
  MultilineStream ms2;
  ms2 << 3 << std::endl;
  ms2 << std::boolalpha << false << std::endl;
  log_debug_m(ms2);

  log_debug("ms2 << ms1");
  ms2 << ms1;
  log_debug_m(ms1);
  log_debug_m(ms2);

  log_debug("ms1 << ms2");
  log_critical_m(ms1);
  log_error_m(ms1);
  log_warning_m(ms1);
  log_info_m(ms1);
  log_debug_m(ms1);
  log_vv_debug_m(ms1);

  log_debug_m(ms2);


  log_debug();

  log_assert(true);
  log_critical();
  log_error();
  log_warning();
  log_info();
  log_debug();
  log_vv_debug();

  firstCallFunc();

  log_critical("Critical");
  log_error("Error");
  log_warning("Warning");
  log_info("Info");
  log_debug("Debug");
  log_vv_debug("Very verbose debug");

  log_critical_s("Critical " << A());
  log_error_s("Error " << A());
  log_warning_s("Warning " << A());
  log_info_s("Info " << A());
  log_debug_s("Debug " << A());
  log_vv_debug_s("Very verbose debug " << A());


  std::string a = log_value("Cool!");
  const char * bc = _lv("Fuck?");
  log_debug(a);
  log_warning(bc);

  int abc = 1;
  log_error_s(abc);

  bool temp = _lv(a.size() > 4);
  log_assert(temp);

  if(_lv(!a.empty()) && _lv(_lv(a.size()) > 3)){}

  log_debug();

  std::string argcStr1 = (argc > 1) ? std::string(argv[1]) : "";


/*  if(argcStr1 == "-h" || argcStr1 == "--help"
     || argcStr1 == "-help" || argcStr1 == "help")
  {
    printHelp(std::string(argv[0]));
    return 0;
  }

  bool isVerbose = (argcStr1 == "-V" || argcStr1 == "-v");
  std::string testPath = (argc > 2) ? std::string(argv[2]) : "";
  if(!isVerbose)
  {
    testPath = argcStr1;
  }

  // Create the event manager and test controller
  CppUnit::TestResult controller;

  // Add a listener that colllects test result
  CppUnit::TestResultCollector result;
  controller.addListener( &result );

  // Add a listener that print dots as test run.
  CppUnit::BriefTestProgressListener verboseProgress;
  CppUnit::TextTestProgressListener shortProgress;
  CppUnit::TestListener *progress = 0;
  if(isVerbose)
  {
    progress = &verboseProgress;
  }
  else
  {
    progress = &shortProgress;
  }

  //CppUnit::BriefTestProgressListener progress;
  controller.addListener( progress );

  // Add the top suite to the test runner
  CppUnit::TestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
  try
  {
    std::cout << "Running "  <<  testPath << std::endl;
    runner.run( controller, testPath );

    std::cerr << std::endl;

    // Print test in a compiler compatible format.
    CppUnit::CompilerOutputter outputter( &result, std::cerr );
    outputter.write();
  }
  catch ( std::invalid_argument &e )  // Test path not resolved
  {
    std::cerr  <<  std::endl
              <<  "ERROR: "  <<  e.what()
              << std::endl;
    return 0;
  }

  return result.wasSuccessful() ? 0 : 1;
*/
  return 0;
}

// end off file
