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

    CPPUNIT_TEST( boardPlusSimpleMove );
    CPPUNIT_TEST( boardPlusSimpleMoveByKing );
    CPPUNIT_TEST( boardPlusSimpleMoveGetKing );
    CPPUNIT_TEST( boardPlusSimpleMoveNoRequestedDraught );
    CPPUNIT_TEST( boardPlusSimpleMoveInWrongDirection );
    CPPUNIT_TEST( boardPlusSimpleMoveToBusySquare );
    CPPUNIT_TEST( boardPlusSimpleMoveJumpExist );

    CPPUNIT_TEST( boardPlusSimpleJump );
    CPPUNIT_TEST( boardPlusSimpleJumpByKing );
    CPPUNIT_TEST( boardPlusSimpleJumpGetKing );
    CPPUNIT_TEST( boardPlusSimpleJumpNoRequestedDraught );
    CPPUNIT_TEST( boardPlusSimpleJumpInWrongDirection );
    CPPUNIT_TEST( boardPlusSimpleJumpToBusySquare );
    CPPUNIT_TEST( boardPlusSimpleJumpMoreJumpExist );
    CPPUNIT_TEST( boardPlusSimpleJumpOverSameColor );

    CPPUNIT_TEST( boardPlusComplexJump );
    CPPUNIT_TEST( boardPlusComplexJumpByKing );
    CPPUNIT_TEST( boardPlusComplexJumpGetKing );
    CPPUNIT_TEST( boardPlusComplexJumpNoRequestedDraught );
    CPPUNIT_TEST( boardPlusComplexJumpInWrongDirection );
    CPPUNIT_TEST( boardPlusComplexJumpToBusySquare );
    CPPUNIT_TEST( boardPlusComplexJumpOverBusySquare );
    CPPUNIT_TEST( boardPlusComplexJumpMoreJumpExist );
    CPPUNIT_TEST( boardPlusComplexJumpNotTerminatedAfterGetKing );
    CPPUNIT_TEST( boardPlusComplexJumpOverSameColor );

    CPPUNIT_TEST( boardMinusSimpleMove );
    CPPUNIT_TEST( boardMinusSimpleMoveByKing );
    CPPUNIT_TEST( boardMinusSimpleMoveLoseKing );
    CPPUNIT_TEST( boardMinusSimpleMoveNoRequestedDraught );
    CPPUNIT_TEST( boardMinusSimpleMoveInWrongDirection );
    CPPUNIT_TEST( boardMinusSimpleMoveToBusySquare );
    CPPUNIT_TEST( boardMinusSimpleMoveJumpExist );

    CPPUNIT_TEST( boardMinusSimpleJump );
    CPPUNIT_TEST( boardMinusSimpleJumpByKing );
    CPPUNIT_TEST( boardMinusSimpleJumpLoseKing );
    CPPUNIT_TEST( boardMinusSimpleJumpNoRequestedDraught );
    CPPUNIT_TEST( boardMinusSimpleJumpInWrongDirection );
    CPPUNIT_TEST( boardMinusSimpleJumpToBusySquare );
    CPPUNIT_TEST( boardMinusSimpleJumpMoreJumpExist );
    CPPUNIT_TEST( boardMinusSimpleJumpOverSameColor );

    CPPUNIT_TEST( boardMinusComplexJump );
    CPPUNIT_TEST( boardMinusComplexJumpByKing );
    CPPUNIT_TEST( boardMinusComplexJumpLoseKing );
    CPPUNIT_TEST( boardMinusComplexJumpNoRequestedDraught );
    CPPUNIT_TEST( boardMinusComplexJumpInWrongDirection );
    CPPUNIT_TEST( boardMinusComplexJumpToBusySquare );
    CPPUNIT_TEST( boardMinusComplexJumpOverBusySquare );
    CPPUNIT_TEST( boardMinusComplexJumpMoreJumpExist );
    CPPUNIT_TEST( boardMinusComplexJumpNotTerminatedAfterGetKing );
    CPPUNIT_TEST( boardMinusComplexJumpOverSameColor );

    CPPUNIT_TEST( boardMinusPlusMoveToGetTheSameBoard );
    CPPUNIT_TEST( boardPlusMinusMoveToGetTheSameBoard );

    CPPUNIT_TEST( boardMinusBoard );
    CPPUNIT_TEST( boardMinusMoveNotFound );
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

  void boardPlusSimpleMove();
  void boardPlusSimpleMoveByKing();
  void boardPlusSimpleMoveGetKing();
  void boardPlusSimpleMoveNoRequestedDraught();
  void boardPlusSimpleMoveInWrongDirection();
  void boardPlusSimpleMoveToBusySquare();
  void boardPlusSimpleMoveJumpExist();

  void boardPlusSimpleJump();
  void boardPlusSimpleJumpByKing();
  void boardPlusSimpleJumpGetKing();
  void boardPlusSimpleJumpNoRequestedDraught();
  void boardPlusSimpleJumpInWrongDirection();
  void boardPlusSimpleJumpToBusySquare();
  void boardPlusSimpleJumpMoreJumpExist();
  void boardPlusSimpleJumpOverSameColor();

  void boardPlusComplexJump();
  void boardPlusComplexJumpByKing();
  void boardPlusComplexJumpGetKing();
  void boardPlusComplexJumpNoRequestedDraught();
  void boardPlusComplexJumpInWrongDirection();
  void boardPlusComplexJumpToBusySquare();
  void boardPlusComplexJumpOverBusySquare();
  void boardPlusComplexJumpMoreJumpExist();
  void boardPlusComplexJumpNotTerminatedAfterGetKing();
  void boardPlusComplexJumpOverSameColor();

  void boardMinusSimpleMove();
  void boardMinusSimpleMoveByKing();
  void boardMinusSimpleMoveLoseKing();
  void boardMinusSimpleMoveNoRequestedDraught();
  void boardMinusSimpleMoveInWrongDirection();
  void boardMinusSimpleMoveToBusySquare();
  void boardMinusSimpleMoveJumpExist();

  void boardMinusSimpleJump();
  void boardMinusSimpleJumpByKing();
  void boardMinusSimpleJumpLoseKing();
  void boardMinusSimpleJumpNoRequestedDraught();
  void boardMinusSimpleJumpInWrongDirection();
  void boardMinusSimpleJumpToBusySquare();
  void boardMinusSimpleJumpMoreJumpExist();
  void boardMinusSimpleJumpOverSameColor();

  void boardMinusComplexJump();
  void boardMinusComplexJumpByKing();
  void boardMinusComplexJumpLoseKing();
  void boardMinusComplexJumpNoRequestedDraught();
  void boardMinusComplexJumpInWrongDirection();
  void boardMinusComplexJumpToBusySquare();
  void boardMinusComplexJumpOverBusySquare();
  void boardMinusComplexJumpMoreJumpExist();
  void boardMinusComplexJumpNotTerminatedAfterGetKing();
  void boardMinusComplexJumpOverSameColor();

  void boardMinusPlusMoveToGetTheSameBoard();
  void boardPlusMinusMoveToGetTheSameBoard();

  void boardMinusBoard();
  void boardMinusMoveNotFound();
};

#endif //H_MOVE_TESTS_H
