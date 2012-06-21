#ifndef H_BOARD_TESTS_H
#define H_BOARD_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class BoardTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( BoardTests );
    CPPUNIT_TEST( put );
    CPPUNIT_TEST( putManOnKingRow );
    CPPUNIT_TEST( takeDraught );
    CPPUNIT_TEST( testSquare );
    CPPUNIT_TEST( equal );
    CPPUNIT_TEST( notEqual );
    CPPUNIT_TEST( less );
    CPPUNIT_TEST( lessBugTest );
    CPPUNIT_TEST( bigger );
    CPPUNIT_TEST( biggerBugTest );
    CPPUNIT_TEST( count );
    CPPUNIT_TEST( countWhite );
    CPPUNIT_TEST( countBlack );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void put();
  void putManOnKingRow();
  void takeDraught();
  void testSquare();
  void equal();
  void notEqual();
  void less();
  void lessBugTest();
  void bigger();
  void biggerBugTest();
  void count();
  void countWhite();
  void countBlack();
};

#endif //H_BOARD_TESTS_H
