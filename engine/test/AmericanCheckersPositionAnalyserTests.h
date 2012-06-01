#ifndef H_AMERICAN_CHECKERS_POSITION_ANALYSER_TESTS_H
#define H_AMERICAN_CHECKERS_POSITION_ANALYSER_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class AmericanCheckersPositionAnalyserTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( AmericanCheckersPositionAnalyserTests );
    //Disable not implemented for a while
    //CPPUNIT_TEST( validMovesSimple );
    //CPPUNIT_TEST( validMovesJump );
    //CPPUNIT_TEST( validMovesBlack );
    //CPPUNIT_TEST( validMovesWhite );
    //CPPUNIT_TEST( validMovesBothColors );
    //CPPUNIT_TEST( validMovesNoMoves );

    CPPUNIT_TEST( createSimpleMove );
    CPPUNIT_TEST( createSimpleMoveByKing );
    CPPUNIT_TEST( createSimpleMoveGetKing );
    CPPUNIT_TEST( createSimpleMoveNoRequestedDraught );
    CPPUNIT_TEST( createSimpleMoveInWrongDirection );
    CPPUNIT_TEST( createSimpleMoveToBusySquare );
    CPPUNIT_TEST( createSimpleMoveJumpExist );

    CPPUNIT_TEST( createSimpleJump );
    CPPUNIT_TEST( createSimpleJumpByKing );
    CPPUNIT_TEST( createSimpleJumpGetKing );
    CPPUNIT_TEST( createSimpleJumpNoRequestedDraught );
    CPPUNIT_TEST( createSimpleJumpNothingToJumpOver );
    CPPUNIT_TEST( createSimpleJumpInWrongDirection );
    CPPUNIT_TEST( createSimpleJumpToBusySquare );
    CPPUNIT_TEST( createSimpleJumpMoreJumpExist );
    CPPUNIT_TEST( createSimpleJumpOverSameColor );

    CPPUNIT_TEST( createComplexJump );
    CPPUNIT_TEST( createComplexJumpByKing );
    CPPUNIT_TEST( createComplexJumpByKingOverStartSquare );
    CPPUNIT_TEST( createComplexJumpByKingOverKingRow );
    CPPUNIT_TEST( createComplexJumpGetKing );
    CPPUNIT_TEST( createComplexJumpNoRequestedDraught );
    CPPUNIT_TEST( createComplexJumpNothingToJumpOver );
    CPPUNIT_TEST( createComplexJumpInWrongDirection );
    CPPUNIT_TEST( createComplexJumpToBusySquare );
    CPPUNIT_TEST( createComplexJumpOverBusySquare );
    CPPUNIT_TEST( createComplexJumpMoreJumpExist );
    CPPUNIT_TEST( createComplexJumpNotTerminatedAfterGetKing );
    CPPUNIT_TEST( createComplexJumpOverSameColor );

    //Disable not implemented for a while
    //CPPUNIT_TEST( createMoveFromTwoBoardsBlack );
    //CPPUNIT_TEST( createMoveFromTwoBoardsWhite );
    //CPPUNIT_TEST( createMoveFromTwoBoardsNotFound );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void validMovesSimple();
  void validMovesJump();
  void validMovesBlack();
  void validMovesWhite();
  void validMovesBothColors();
  void validMovesNoMoves();

  void createSimpleMove();
  void createSimpleMoveByKing();
  void createSimpleMoveGetKing();
  void createSimpleMoveNoRequestedDraught();
  void createSimpleMoveInWrongDirection();
  void createSimpleMoveToBusySquare();
  void createSimpleMoveJumpExist();

  void createSimpleJump();
  void createSimpleJumpByKing();
  void createSimpleJumpGetKing();
  void createSimpleJumpNoRequestedDraught();
  void createSimpleJumpNothingToJumpOver();
  void createSimpleJumpInWrongDirection();
  void createSimpleJumpToBusySquare();
  void createSimpleJumpMoreJumpExist();
  void createSimpleJumpOverSameColor();

  void createComplexJump();
  void createComplexJumpByKing();
  void createComplexJumpByKingOverStartSquare();
  void createComplexJumpByKingOverKingRow();
  void createComplexJumpGetKing();
  void createComplexJumpNoRequestedDraught();
  void createComplexJumpNothingToJumpOver();
  void createComplexJumpInWrongDirection();
  void createComplexJumpToBusySquare();
  void createComplexJumpOverBusySquare();
  void createComplexJumpMoreJumpExist();
  void createComplexJumpNotTerminatedAfterGetKing();
  void createComplexJumpOverSameColor();

  void createMoveFromTwoBoardsBlack();
  void createMoveFromTwoBoardsWhite();
  void createMoveFromTwoBoardsNotFound();
};

#endif //H_AMERICAN_CHECKERS_POSITION_ANALYSER_TESTS_H
