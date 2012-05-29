#ifndef H_COORD_SEQUENCE_TESTS_H
#define H_COORD_SEQUENCE_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class CoordSequenceTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( CoordSequenceTests );
    CPPUNIT_TEST( wrongSequenceForSimpleMove );
    CPPUNIT_TEST( wrongSequenceForJump );
    CPPUNIT_TEST( equal );
    CPPUNIT_TEST( notEqual );
    CPPUNIT_TEST( beginAndEnd );
    CPPUNIT_TEST( second );
    CPPUNIT_TEST( thirdFromEnd );
    CPPUNIT_TEST( secondFromEnd );
    CPPUNIT_TEST( last );
    CPPUNIT_TEST( count );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void wrongSequenceForSimpleMove();
  void wrongSequenceForJump();
  void equal();
  void notEqual();
  void beginAndEnd();
  void second();
  void thirdFromEnd();
  void secondFromEnd();
  void last();
  void count();
};

#endif //H_COORD_SEQUENCE_TESTS_H
