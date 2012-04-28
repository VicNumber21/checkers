#ifndef H_BOARD_VIEW_TESTS_H
#define H_BOARD_VIEW_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class BoardViewTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( BoardViewTests );
    CPPUNIT_TEST( emptyBoard );
    CPPUNIT_TEST( rotation );
    CPPUNIT_TEST( draughtChars );
    CPPUNIT_TEST( complexPosition );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void emptyBoard();
  void rotation();
  void draughtChars();
  void complexPosition();
};

#endif //H_BOARD_VIEW_TESTS_H
