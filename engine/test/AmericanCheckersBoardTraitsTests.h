#ifndef H_AMERICAN_CHECKERS_BOARD_TRAITS_TESTS_H
#define H_AMERICAN_CHECKERS_BOARD_TRAITS_TESTS_H

#include "AmericanCheckersBoardTraits.h"

#include <cppunit/extensions/HelperMacros.h>
#include <vector>


class AmericanCheckersBoardTraitsTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( AmericanCheckersBoardTraitsTests );
    CPPUNIT_TEST( bounds );
    CPPUNIT_TEST( nameIndexMap );
    CPPUNIT_TEST( kingRow );
    CPPUNIT_TEST( squareColor );
  CPPUNIT_TEST_SUITE_END();

public:
  AmericanCheckersBoardTraitsTests();

  virtual void setUp();
  virtual void tearDown();

  void bounds();
  void nameIndexMap();
  void kingRow();
  void squareColor();

private:
  Checkers::Engine::AmericanCheckersBoardTraits m_board_traits;
  const int m_board_height_width;
  std::vector<char> m_row_names;
  std::vector<char> m_column_names;
};

#endif //H_AMERICAN_CHECKERS_BOARD_TRAITS_TESTS_H
