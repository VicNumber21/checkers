#ifndef H_COORD_DELTA_TESTS_H
#define H_COORD_DELTA_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class CoordDeltaTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( CoordDeltaTests );
    CPPUNIT_TEST( deltaXY );
    CPPUNIT_TEST( geometryProperties );
    CPPUNIT_TEST( isSymmetric );
    CPPUNIT_TEST( direction );
    CPPUNIT_TEST( distance );
    CPPUNIT_TEST( CoordPlusDelta );
    CPPUNIT_TEST( CoordMinusDelta );
    CPPUNIT_TEST( CoordMinusCoord );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void deltaXY();
  void geometryProperties();
  void isSymmetric();
  void direction();
  void distance();
  void CoordPlusDelta();
  void CoordMinusDelta();
  void CoordMinusCoord();
};

#endif //H_COORD_DELTA_TESTS_H
