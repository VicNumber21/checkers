#ifndef H_MOVE_TESTS_H
#define H_MOVE_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class MoveTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MoveTests );
    CPPUNIT_TEST( undefinedUsage );
    CPPUNIT_TEST( unexpectedAppend );
    CPPUNIT_TEST( wrongSequenceForSimpleMove );
    CPPUNIT_TEST( wrongSequenceForJump );
    CPPUNIT_TEST( equal );
    CPPUNIT_TEST( notEqual );
    CPPUNIT_TEST( type );
    CPPUNIT_TEST( simpleMoveScore );
    CPPUNIT_TEST( simpleJumpScore );
    CPPUNIT_TEST( complexJumpScore );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void undefinedUsage();
  void unexpectedAppend();
  void wrongSequenceForSimpleMove();
  void wrongSequenceForJump();
  void equal();
  void notEqual();
  void type();
  void simpleMoveScore();
  void simpleJumpScore();
  void complexJumpScore();
};

#endif //H_MOVE_TESTS_H
