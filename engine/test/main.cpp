#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TextTestProgressListener.h>

#include <stdexcept>


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

int
main( int argc, char* argv[] )
{
  std::string argcStr1 = (argc > 1) ? std::string(argv[1]) : "";

  if(argcStr1 == "-h" || argcStr1 == "--help"
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
}

// end off file
