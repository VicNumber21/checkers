#ifndef H_FRAMED_BOARD_VIEW_TESTS_H
#define H_FRAMED_BOARD_VIEW_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class FramedBoardViewTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( FramedBoardViewTests );
    CPPUNIT_TEST( emptyBoard );
    CPPUNIT_TEST( rotation );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void emptyBoard();
  void rotation();
};

#endif //H_FRAMED_BOARD_VIEW_TESTS_H
