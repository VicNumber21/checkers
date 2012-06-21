#ifndef H_MOVE_TESTS_H
#define H_MOVE_TESTS_H

#include "Move.h"

#include <cppunit/extensions/HelperMacros.h>


class MoveTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MoveTests );
    CPPUNIT_TEST( undefinedUsage );
    CPPUNIT_TEST( wrongConstruction );
    CPPUNIT_TEST( equalError );
    CPPUNIT_TEST( equalSimpleMove );
    CPPUNIT_TEST( equalSimpleJump );
    CPPUNIT_TEST( equalComplexJump );
    CPPUNIT_TEST( notEqualError );
    CPPUNIT_TEST( notEqualSimpleMove );
    CPPUNIT_TEST( notEqualSimpleJump );
    CPPUNIT_TEST( notEqualComplexJump );
    CPPUNIT_TEST( type );
    CPPUNIT_TEST( isValid );
    CPPUNIT_TEST( error );
    CPPUNIT_TEST( simpleMoveScore );
    CPPUNIT_TEST( simpleJumpScore );
    CPPUNIT_TEST( complexJumpScore );
    CPPUNIT_TEST( coordSequenceId );
  CPPUNIT_TEST_SUITE_END();

public:
  MoveTests();

  virtual void setUp();
  virtual void tearDown();

  void undefinedUsage();
  void wrongConstruction();
  void equalError();
  void equalSimpleMove();
  void equalSimpleJump();
  void equalComplexJump();
  void notEqualError();
  void notEqualSimpleMove();
  void notEqualSimpleJump();
  void notEqualComplexJump();
  void type();
  void isValid();
  void error();
  void simpleMoveScore();
  void simpleJumpScore();
  void complexJumpScore();
  void coordSequenceId();

private:
  Checkers::Engine::Move m_empty_move;
  Checkers::Engine::Move m_error_move_1;
  Checkers::Engine::Move m_error_move_2;
  Checkers::Engine::Move m_simple_move_1_any_id;
  Checkers::Engine::Move m_simple_move_1_id_2;
  Checkers::Engine::Move m_simple_move_2;
  Checkers::Engine::Move m_simple_jump_1;
  Checkers::Engine::Move m_simple_jump_2;
  Checkers::Engine::Move m_complex_jump_1;
  Checkers::Engine::Move m_complex_jump_2;
};

#endif //H_MOVE_TESTS_H
