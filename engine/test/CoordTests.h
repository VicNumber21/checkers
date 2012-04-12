#ifndef H_COORD_TESTS_H
#define H_COORD_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class CoordTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( CoordTests );
    CPPUNIT_TEST( wrongIntCoord );
    CPPUNIT_TEST( wrongCharCoord );
    CPPUNIT_TEST( noValueUse );
    CPPUNIT_TEST( less );
    CPPUNIT_TEST( equal );
    CPPUNIT_TEST( notEqual );
    CPPUNIT_TEST( greater );
    CPPUNIT_TEST( setWrongIntCoord );
    CPPUNIT_TEST( setWrongCharCoord );
    CPPUNIT_TEST( normalCase );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void wrongIntCoord();
  void wrongCharCoord();
  void noValueUse();
  void less();
  void equal();
  void notEqual();
  void greater();
  void setWrongIntCoord();
  void setWrongCharCoord();
  void normalCase();
};

#endif //H_COORD_TESTS_H
