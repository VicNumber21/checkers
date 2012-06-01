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
    CPPUNIT_TEST( boardPlusSimpleJumpNothingToJumpOver );
    CPPUNIT_TEST( boardPlusSimpleJumpInWrongDirection );
    CPPUNIT_TEST( boardPlusSimpleJumpToBusySquare );
    CPPUNIT_TEST( boardPlusSimpleJumpMoreJumpExist );
    CPPUNIT_TEST( boardPlusSimpleJumpOverSameColor );

    CPPUNIT_TEST( boardPlusComplexJump );
    CPPUNIT_TEST( boardPlusComplexJumpByKing );
    CPPUNIT_TEST( boardPlusComplexJumpByKingOverStartSquare );
    CPPUNIT_TEST( boardPlusComplexJumpByKingOverKingRow );
    CPPUNIT_TEST( boardPlusComplexJumpGetKing );
    CPPUNIT_TEST( boardPlusComplexJumpNoRequestedDraught );
    CPPUNIT_TEST( boardPlusComplexJumpNothingToJumpOver );
    CPPUNIT_TEST( boardPlusComplexJumpInWrongDirection );
    CPPUNIT_TEST( boardPlusComplexJumpToBusySquare );
    CPPUNIT_TEST( boardPlusComplexJumpOverBusySquare );
    CPPUNIT_TEST( boardPlusComplexJumpMoreJumpExist );
    CPPUNIT_TEST( boardPlusComplexJumpNotTerminatedAfterGetKing );
    CPPUNIT_TEST( boardPlusComplexJumpOverSameColor );
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
  void boardPlusSimpleJumpNothingToJumpOver();
  void boardPlusSimpleJumpInWrongDirection();
  void boardPlusSimpleJumpToBusySquare();
  void boardPlusSimpleJumpMoreJumpExist();
  void boardPlusSimpleJumpOverSameColor();

  void boardPlusComplexJump();
  void boardPlusComplexJumpByKing();
  void boardPlusComplexJumpByKingOverStartSquare();
  void boardPlusComplexJumpByKingOverKingRow();
  void boardPlusComplexJumpGetKing();
  void boardPlusComplexJumpNoRequestedDraught();
  void boardPlusComplexJumpNothingToJumpOver();
  void boardPlusComplexJumpInWrongDirection();
  void boardPlusComplexJumpToBusySquare();
  void boardPlusComplexJumpOverBusySquare();
  void boardPlusComplexJumpMoreJumpExist();
  void boardPlusComplexJumpNotTerminatedAfterGetKing();
  void boardPlusComplexJumpOverSameColor();
};

#endif //H_MOVE_TESTS_H
