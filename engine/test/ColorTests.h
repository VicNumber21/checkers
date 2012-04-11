#ifndef H_COLOR_TESTS_H
#define H_COLOR_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class ColorTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( ColorTests );
    CPPUNIT_TEST( equalToEnum );
    CPPUNIT_TEST( notEqualToEnum );
    CPPUNIT_TEST( equalToColor );
    CPPUNIT_TEST( notEqualToColor );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void equalToEnum();
  void notEqualToEnum();
  void equalToColor();
  void notEqualToColor();
};

#endif //H_COLOR_TESTS_H
