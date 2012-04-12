#ifndef H_DRAUGHT_TESTS_H
#define H_DRAUGHT_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class DraughtTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( DraughtTests );
    CPPUNIT_TEST( coordAndColor );
    CPPUNIT_TEST( theSameCoordDifferentColor );
    CPPUNIT_TEST( theSameColorDifferentCoord );
    CPPUNIT_TEST( equal );
    CPPUNIT_TEST( notEqual );
    CPPUNIT_TEST( bigger );
    CPPUNIT_TEST( less );
    CPPUNIT_TEST( moveTo );
    CPPUNIT_TEST( makeKing );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void coordAndColor();
  void theSameCoordDifferentColor();
  void theSameColorDifferentCoord();
  void equal();
  void notEqual();
  void bigger();
  void less();
  void moveTo();
  void makeKing();
};

#endif //H_DRAUGHT_TESTS_H
