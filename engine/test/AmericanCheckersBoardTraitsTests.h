#ifndef H_AMERICAN_CHECKERS_BOARD_TRAITS_TESTS_H
#define H_AMERICAN_CHECKERS_BOARD_TRAITS_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class AmericanCheckersBoardTraitsTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( AmericanCheckersBoardTraitsTests );
    CPPUNIT_TEST( bounds );
    CPPUNIT_TEST( nameIndexMap );
    CPPUNIT_TEST( kingLine );
    CPPUNIT_TEST( squareColor );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void bounds();
  void nameIndexMap();
  void kingLine();
  void squareColor();
};

#endif //H_AMERICAN_CHECKERS_BOARD_TRAITS_TESTS_H
