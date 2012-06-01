#include "AmericanCheckersPositionAnalyserTests.h"
#include "AmericanCheckersPositionAnalyser.h"
#include "Move.h"
#include "CoordSequence.h"
#include "Board.h"
#include "Draught.h"
#include "Color.h"
#include "Coord.h"
#include "PrettyPrint.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( AmericanCheckersPositionAnalyserTests );


void AmericanCheckersPositionAnalyserTests::setUp()
{
}

void AmericanCheckersPositionAnalyserTests::tearDown()
{
}

void AmericanCheckersPositionAnalyserTests::validMovesSimple()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::validMovesJump()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::validMovesBlack()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::validMovesWhite()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::validMovesBothColors()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::validMovesNoMoves()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::createSimpleMove()
{
  const Coord cBlackStart('c', '3');
  const Coord cBlackLeftForward('b', '4');
  const Coord cBlackRightForward('d', '4');

  const Coord cWhiteStart('f', '6');
  const Coord cWhiteLeftForward('g', '5');
  const Coord cWhiteRightForward('e', '5');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveByKing()
{
  const Coord cBlackStart('c', '3');
  const Coord cBlackLeftForward('b', '4');
  const Coord cBlackRightForward('d', '4');
  const Coord cBlackLeftBack('b', '2');
  const Coord cBlackRightBack('d', '2');

  const Coord cWhiteStart('f', '6');
  const Coord cWhiteLeftForward('g', '5');
  const Coord cWhiteRightForward('e', '5');
  const Coord cWhiteLeftBack('g', '7');
  const Coord cWhiteRightBack('e', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csBlackLeftBack(cBlackStart, cBlackLeftBack);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, m.to());

  CoordSequence csBlackRightBack(cBlackStart, cBlackRightBack);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());

  CoordSequence csWhiteRightBack(cWhiteStart, cWhiteRightBack);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, m.to());

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveGetKing()
{
  const Coord cBlackStart('c', '7');
  const Coord cBlackLeftForward('b', '8');
  const Coord cBlackRightForward('d', '8');

  const Coord cWhiteStart('f', '2');
  const Coord cWhiteLeftForward('g', '1');
  const Coord cWhiteRightForward('e', '1');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveNoRequestedDraught()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackWrongStart('e', '5');
  const Coord cBlackMoveTo('d', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));

  Move mBlack(cBlackWrongStart, cBlackMoveTo);
  CPPUNIT_ASSERT_THROW(b + mBlack, Move::ErrorNoRequestedDraught);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveInWrongDirection()
{
  const Coord cBlackStart('c', '7');
  const Coord cBlackLeftBack('b', '6');
  const Coord cBlackRightBack('d', '6');

  const Coord cWhiteStart('f', '2');
  const Coord cWhiteLeftBack('g', '3');
  const Coord cWhiteRightBack('e', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  Move mBlackLeftBack(cBlackStart, cBlackLeftBack);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftBack, Move::ErrorInWrongDirection);

  Move mBlackRightBack(cBlackStart, cBlackRightBack);
  CPPUNIT_ASSERT_THROW(b + mBlackRightBack, Move::ErrorInWrongDirection);

  Move mWhiteRightBack(cWhiteStart, cWhiteRightBack);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightBack, Move::ErrorInWrongDirection);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftBack, Move::ErrorInWrongDirection);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveToBusySquare()
{
  const Coord cBlackStart('d', '4');
  const Coord cBlackLeftForward('c', '5');

  const Coord cWhiteStart('e', '5');
  const Coord cWhiteLeftForward('f', '4');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cBlackLeftForward, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cWhiteLeftForward, Color::EWhite));

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftForward, Move::ErrorToBusySquare);

  Move mBlackRightForward(cBlackStart, cWhiteStart);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorToBusySquare);

  Move mWhiteRightForward(cWhiteStart, cBlackStart);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightForward, Move::ErrorToBusySquare);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftForward, Move::ErrorToBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveJumpExist()
{
  const Coord cBlackStart('d', '4');
  const Coord cBlackLeftForward('c', '5');

  const Coord cWhiteStart('e', '5');
  const Coord cWhiteLeftForward('f', '4');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftForward, Move::ErrorJumpExist);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftForward, Move::ErrorJumpExist);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJump()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack('f', '4');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite('c', '5');
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteRightForward('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpByKing()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack1('f', '4');
  const Coord cAnotherBlack2('f', '6');
  const Coord cAnotherBlack3('d', '6');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackLeftBack('b', '2');
  const Coord cBlackRightBack('f', '2');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite1('c', '5');
  const Coord cAnotherWhite2('c', '3');
  const Coord cAnotherWhite3('e', '3');
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteLeftBack('g', '7');
  const Coord cWhiteRightBack('c', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack, true));
  b.put(Draught(cAnotherBlack1, Color::EBlack));
  b.put(Draught(cAnotherBlack2, Color::EBlack, true));
  b.put(Draught(cAnotherBlack3, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cAnotherWhite1, Color::EWhite));
  b.put(Draught(cAnotherWhite2, Color::EWhite));
  b.put(Draught(cAnotherWhite3, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackLeftBack(cBlackStart, cBlackLeftBack);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterBlackLeftBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, m.to());

  CoordSequence csBlackRightBack(cBlackStart, cBlackRightBack);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackRightBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterBlackRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csBlackRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());

  CoordSequence csWhiteRightBack(cWhiteStart, cWhiteRightBack);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteRightBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, m.to());

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpGetKing()
{
  const Coord cBlackStart('d', '6');
  const Coord cAnotherBlack1('d', '2');
  const Coord cAnotherBlack2('f', '2');
  const Coord cBlackLeftForward('b', '8');
  const Coord cBlackRightForward('f', '8');

  const Coord cWhiteStart('e', '3');
  const Coord cAnotherWhite1('c', '7');
  const Coord cAnotherWhite2('e', '7');
  const Coord cWhiteLeftForward('g', '1');
  const Coord cWhiteRightForward('c', '1');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack1, Color::EBlack));
  b.put(Draught(cAnotherBlack2, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite1, Color::EWhite, true));
  b.put(Draught(cAnotherWhite2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackRightForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpNoRequestedDraught()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackWrongStart('g', '5');
  const Coord cBlackMoveTo('e', '7');

  const Coord cWhite1('d', '6');
  const Coord cWhite2('f', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhite1, Color::EWhite));
  b.put(Draught(cWhite1, Color::EWhite, true));

  Move mBlack(cBlackWrongStart, cBlackMoveTo, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlack, Move::ErrorNoRequestedDraught);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpNothingToJumpOver()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackMoveTo('e', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  Move mBlack(cBlackStart, cBlackMoveTo, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlack, Move::ErrorNothingToJumpOver);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpInWrongDirection()
{
  const Coord cBlackStart('c', '5');
  const Coord cAnotherBlack('e', '5');
  const Coord cBlackLeftBack('a', '3');
  const Coord cBlackRightBack('e', '3');

  const Coord cWhiteStart('d', '4');
  const Coord cAnotherWhite('b', '4');
  const Coord cWhiteLeftBack('b', '6');
  const Coord cWhiteRightBack('f', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  Move mBlackLeftBack(cBlackStart, cBlackLeftBack, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftBack, Move::ErrorInWrongDirection);

  Move mBlackRightBack(cBlackStart, cBlackRightBack, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackRightBack, Move::ErrorInWrongDirection);

  Move mWhiteRightBack(cWhiteStart, cWhiteRightBack, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightBack, Move::ErrorInWrongDirection);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftBack, Move::ErrorInWrongDirection);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpToBusySquare()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack1('f', '4');
  const Coord cAnotherBlack2('e', '3');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite1('c', '5');
  const Coord cAnotherWhite2('d', '6');
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteRightForward('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack1, Color::EBlack, true));
  b.put(Draught(cAnotherBlack2, Color::EBlack));
  b.put(Draught(cBlackLeftForward, Color::EWhite, true));
  b.put(Draught(cBlackRightForward, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite1, Color::EWhite));
  b.put(Draught(cAnotherWhite2, Color::EWhite));
  b.put(Draught(cWhiteLeftForward, Color::EBlack));
  b.put(Draught(cWhiteRightForward, Color::EWhite));

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftForward, Move::ErrorToBusySquare);

  Move mBlackRightForward(cBlackStart, cBlackRightForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorToBusySquare);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightForward, Move::ErrorToBusySquare);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftForward, Move::ErrorToBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpMoreJumpExist()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack('b', '4');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite('g', '7');
  const Coord cWhiteRightForward('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  Move mBlackRightForward(cBlackStart, cBlackRightForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorJumpExist);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightForward, Move::ErrorJumpExist);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpOverSameColor()
{
  const Coord cBlackStart('b', '4');
  const Coord cAnotherBlack('c', '5');
  const Coord cBlackRightForward('d', '6');

  const Coord cWhiteStart('f', '4');
  const Coord cAnotherWhite('g', '5');
  const Coord cWhiteLeftBack('h', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  Move mBlackRightForward(cBlackStart, cBlackRightForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorJumpOverSameColor);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftBack, Move::ErrorJumpOverSameColor);
}

void AmericanCheckersPositionAnalyserTests::createComplexJump()
{
  const Coord cBlackStart('c', '1');
  const Coord cAnotherBlack1('e', '3');
  const Coord cAnotherBlack2('g', '3');
  const Coord cAnotherBlack3('g', '5');
  const Coord cAnotherBlack4('g', '7');
  const Coord cBlackJump1('a', '3');
  const Coord cBlackJump2('c', '5');
  const Coord cBlackJump3LeftForward('a', '7');
  const Coord cBlackJump3RightForward('e', '7');

  const Coord cWhiteStart('f', '8');
  const Coord cAnotherWhite1('b', '6');
  const Coord cAnotherWhite2('d', '6');
  const Coord cAnotherWhite3('b', '4');
  const Coord cAnotherWhite4('b', '2');
  const Coord cWhiteJump1('h', '6');
  const Coord cWhiteJump2('f', '4');
  const Coord cWhiteJump3LeftForward('h', '2');
  const Coord cWhiteJump3RightForward('d', '2');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack1, Color::EBlack));
  b.put(Draught(cAnotherBlack2, Color::EBlack));
  b.put(Draught(cAnotherBlack3, Color::EBlack, true));
  b.put(Draught(cAnotherBlack4, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite1, Color::EWhite));
  b.put(Draught(cAnotherWhite2, Color::EWhite, true));
  b.put(Draught(cAnotherWhite3, Color::EWhite));
  b.put(Draught(cAnotherWhite4, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackAtTheEndLeftForward(cBlackStart, cBlackJump1);
  csBlackAtTheEndLeftForward.append(cBlackJump2);
  CoordSequence csBlackAtTheEndRightForward(csBlackAtTheEndLeftForward);
  csBlackAtTheEndLeftForward.append(cBlackJump3LeftForward);
  csBlackAtTheEndRightForward.append(cBlackJump3RightForward);

  Board bBlackAtTheEndLeftForward;
  bBlackAtTheEndLeftForward.put(Draught(cBlackJump3LeftForward, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack3, Color::EBlack, true));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack4, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  m = analyser.createMove(csBlackAtTheEndLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackAtTheEndLeftForward, m.to());

  Board bBlackAtTheEndRightForward;
  bBlackAtTheEndRightForward.put(Draught(cBlackJump3RightForward, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack3, Color::EBlack, true));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack4, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bBlackAtTheEndRightForward.put(Draught(cAnotherWhite1, Color::EWhite));
  m = analyser.createMove(csBlackAtTheEndRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackAtTheEndRightForward, m.to());

  CoordSequence csWhiteAtTheEndLeftForward(cWhiteStart, cWhiteJump1);
  csWhiteAtTheEndLeftForward.append(cWhiteJump2);
  CoordSequence csWhiteAtTheEndRightForward(csWhiteAtTheEndLeftForward);
  csWhiteAtTheEndLeftForward.append(cWhiteJump3LeftForward);
  csWhiteAtTheEndRightForward.append(cWhiteJump3RightForward);

  Board bWhiteAtTheEndLeftForward;
  bWhiteAtTheEndLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bWhiteAtTheEndLeftForward.put(Draught(cWhiteJump3LeftForward, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite3, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite4, Color::EWhite));
  m = analyser.createMove(csWhiteAtTheEndLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteAtTheEndLeftForward, m.to());

  Board bWhiteAtTheEndRightForward;
  bWhiteAtTheEndRightForward.put(Draught(cBlackStart, Color::EBlack));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bWhiteAtTheEndRightForward.put(Draught(cWhiteJump3RightForward, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite3, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite4, Color::EWhite));
  m = analyser.createMove(csWhiteAtTheEndRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteAtTheEndRightForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpByKing()
{
  const Coord cBlackStartE3('e', '3');
  const Coord cBlackG3('g', '3');
  const Coord cBlackE5('e', '5');
  const Coord cBlackG5('g', '5');
  const Coord cBlackE7('e', '7');
  const Coord cBlackG7('g', '7');
  const Coord cBlackJumpC1('c', '1');
  const Coord cBlackJumpA3('a', '3');
  const Coord cBlackJumpC5('c', '5');
  const Coord cBlackJumpA7('a', '7');

  const Coord cWhiteStartD6('d', '6');
  const Coord cWhiteB6('b', '6');
  const Coord cWhiteB4('b', '4');
  const Coord cWhiteD4('d', '4');
  const Coord cWhiteB2('b', '2');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteJumpF8('f', '8');
  const Coord cWhiteJumpH6('h', '6');
  const Coord cWhiteJumpF4('f', '4');
  const Coord cWhiteJumpH2('h', '2');

  Board b;
  b.put(Draught(cBlackStartE3, Color::EBlack, true));
  b.put(Draught(cBlackG3, Color::EBlack));
  b.put(Draught(cBlackG5, Color::EBlack));
  b.put(Draught(cBlackG7, Color::EBlack, true));
  b.put(Draught(cBlackE5, Color::EBlack));
  b.put(Draught(cBlackE7, Color::EBlack));
  b.put(Draught(cWhiteStartD6, Color::EWhite, true));
  b.put(Draught(cWhiteB6, Color::EWhite));
  b.put(Draught(cWhiteB4, Color::EWhite, true));
  b.put(Draught(cWhiteB2, Color::EWhite));
  b.put(Draught(cWhiteD4, Color::EWhite));
  b.put(Draught(cWhiteD2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackE3C1_E3(cBlackStartE3, cBlackJumpC1);
  csBlackE3C1_E3.append(cBlackJumpA3);
  csBlackE3C1_E3.append(cBlackJumpC5);
  CoordSequence csBlackE3C1_A7(csBlackE3C1_E3);
  csBlackE3C1_E3.append(cBlackStartE3);
  csBlackE3C1_A7.append(cBlackJumpA7);

  Board bBlackE3C1_E3;
  bBlackE3C1_E3.put(Draught(cBlackStartE3, Color::EBlack, true));
  bBlackE3C1_E3.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_E3.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_E3.put(Draught(cWhiteB6, Color::EWhite));
  m = analyser.createMove(csBlackE3C1_E3);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_E3, m.to());

  Board bBlackE3C1_A7;
  bBlackE3C1_A7.put(Draught(cBlackJumpA7, Color::EBlack, true));
  bBlackE3C1_A7.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_A7.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_A7.put(Draught(cWhiteD4, Color::EWhite));
  m = analyser.createMove(csBlackE3C1_A7);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_A7, m.to());

  CoordSequence csBlackE3C5_E3(cBlackStartE3, cBlackJumpC5);
  CoordSequence csBlackE3C5_A7(csBlackE3C5_E3);
  csBlackE3C5_E3.append(cBlackJumpA3);
  csBlackE3C5_E3.append(cBlackJumpC1);
  csBlackE3C5_E3.append(cBlackStartE3);
  csBlackE3C5_A7.append(cBlackJumpA7);

  m = analyser.createMove(csBlackE3C5_E3);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_E3, m.to()); //the same board as jump in another direction

  Board bBlackE3C5_A7;
  bBlackE3C5_A7.put(Draught(cBlackJumpA7, Color::EBlack, true));
  bBlackE3C5_A7.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C5_A7.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C5_A7.put(Draught(cWhiteB4, Color::EWhite, true));
  bBlackE3C5_A7.put(Draught(cWhiteB2, Color::EWhite));
  bBlackE3C5_A7.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csBlackE3C5_A7);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C5_A7, m.to());

  CoordSequence csWhiteD6F8_D6(cWhiteStartD6, cWhiteJumpF8);
  csWhiteD6F8_D6.append(cWhiteJumpH6);
  csWhiteD6F8_D6.append(cWhiteJumpF4);
  CoordSequence csWhiteD6F8_H2(csWhiteD6F8_D6);
  csWhiteD6F8_D6.append(cWhiteStartD6);
  csWhiteD6F8_H2.append(cWhiteJumpH2);

  Board bWhiteD6F8_D6;
  bWhiteD6F8_D6.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_D6.put(Draught(cBlackG3, Color::EBlack));
  bWhiteD6F8_D6.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bWhiteD6F8_D6.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_D6.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F8_D6);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_D6, m.to());

  Board bWhiteD6F8_H2;
  bWhiteD6F8_H2.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_H2.put(Draught(cBlackE5, Color::EBlack));
  bWhiteD6F8_H2.put(Draught(cWhiteJumpH2, Color::EWhite, true));
  bWhiteD6F8_H2.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_H2.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F8_H2);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_H2, m.to());

  CoordSequence csWhiteD6F4_D6(cWhiteStartD6, cWhiteJumpF4);
  CoordSequence csWhiteD6F4_H2(csWhiteD6F4_D6);
  csWhiteD6F4_D6.append(cWhiteJumpH6);
  csWhiteD6F4_D6.append(cWhiteJumpF8);
  csWhiteD6F4_D6.append(cWhiteStartD6);
  csWhiteD6F4_H2.append(cWhiteJumpH2);

  m = analyser.createMove(csWhiteD6F4_D6);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_D6, m.to()); //the same board as jump in another direction

  Board bWhiteD6F4_H2;
  bWhiteD6F4_H2.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F4_H2.put(Draught(cBlackG5, Color::EBlack));
  bWhiteD6F4_H2.put(Draught(cBlackG7, Color::EBlack, true));
  bWhiteD6F4_H2.put(Draught(cBlackE7, Color::EBlack));
  bWhiteD6F4_H2.put(Draught(cWhiteJumpH2, Color::EWhite, true));
  bWhiteD6F4_H2.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F4_H2.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F4_H2.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F4_H2.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F4_H2.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F4_H2);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F4_H2, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpByKingOverKingRow()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpF6('f', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite, true));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D4(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D4.append(cBlackJumpD8);
  csBlackD4B6_D4.append(cBlackJumpF6);
  csBlackD4B6_D4.append(cBlackStartD4);
  Board bBlackD4_D4;
  bBlackD4_D4.put(Draught(cBlackStartD4, Color::EBlack, true));
  bBlackD4_D4.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4_D4.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4_D4.put(Draught(cBlackF2, Color::EBlack));
  m = analyser.createMove(csBlackD4B6_D4);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4_D4, m.to());

  CoordSequence csBlackD4F6_D4(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_D4.append(cBlackJumpD8);
  csBlackD4F6_D4.append(cBlackJumpB6);
  csBlackD4F6_D4.append(cBlackStartD4);
  m = analyser.createMove(csBlackD4F6_D4);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4_D4, m.to());

  CoordSequence csWhiteE5C3_E5(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E5.append(cWhiteJumpE1);
  csWhiteE5C3_E5.append(cWhiteJumpG3);
  csWhiteE5C3_E5.append(cWhiteStartE5);
  Board bWhiteE5_E5;
  bWhiteE5_E5.put(Draught(cWhiteStartE5, Color::EWhite, true));
  bWhiteE5_E5.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5_E5.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5_E5.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteE5C3_E5);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5_E5, m.to());

  CoordSequence csWhiteE5G3_E5(cWhiteStartE5, cWhiteJumpG3);
  csWhiteE5G3_E5.append(cWhiteJumpE1);
  csWhiteE5G3_E5.append(cWhiteJumpC3);
  csWhiteE5G3_E5.append(cWhiteStartE5);
  m = analyser.createMove(csWhiteE5G3_E5);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5_E5, m.to());
}
void AmericanCheckersPositionAnalyserTests::createComplexJumpByKingOverStartSquare()
{
  const Coord cBlackStartE3('e', '3');
  const Coord cBlackG3('g', '3');
  const Coord cBlackE5('e', '5');
  const Coord cBlackG5('g', '5');
  const Coord cBlackE7('e', '7');
  const Coord cBlackG7('g', '7');
  const Coord cBlackC7('c', '7');
  const Coord cBlackJumpC1('c', '1');
  const Coord cBlackJumpA3('a', '3');
  const Coord cBlackJumpC5('c', '5');
  const Coord cBlackJumpG1('g', '1');

  const Coord cWhiteStartD6('d', '6');
  const Coord cWhiteB6('b', '6');
  const Coord cWhiteB4('b', '4');
  const Coord cWhiteD4('d', '4');
  const Coord cWhiteB2('b', '2');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteF2('f', '2');
  const Coord cWhiteJumpF8('f', '8');
  const Coord cWhiteJumpH6('h', '6');
  const Coord cWhiteJumpF4('f', '4');
  const Coord cWhiteJumpB8('b', '8');

  Board b;
  b.put(Draught(cBlackStartE3, Color::EBlack, true));
  b.put(Draught(cBlackG3, Color::EBlack));
  b.put(Draught(cBlackG5, Color::EBlack));
  b.put(Draught(cBlackG7, Color::EBlack, true));
  b.put(Draught(cBlackE5, Color::EBlack));
  b.put(Draught(cBlackE7, Color::EBlack));
  b.put(Draught(cBlackC7, Color::EBlack, true));
  b.put(Draught(cWhiteStartD6, Color::EWhite, true));
  b.put(Draught(cWhiteB6, Color::EWhite));
  b.put(Draught(cWhiteB4, Color::EWhite, true));
  b.put(Draught(cWhiteB2, Color::EWhite));
  b.put(Draught(cWhiteD4, Color::EWhite));
  b.put(Draught(cWhiteD2, Color::EWhite));
  b.put(Draught(cWhiteF2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackE3C1_G1(cBlackStartE3, cBlackJumpC1);
  csBlackE3C1_G1.append(cBlackJumpA3);
  csBlackE3C1_G1.append(cBlackJumpC5);
  csBlackE3C1_G1.append(cBlackStartE3);
  csBlackE3C1_G1.append(cBlackJumpG1);

  Board bBlackE3C1_G1;
  bBlackE3C1_G1.put(Draught(cBlackJumpG1, Color::EBlack, true));
  bBlackE3C1_G1.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_G1.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackC7, Color::EBlack, true));
  bBlackE3C1_G1.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_G1.put(Draught(cWhiteB6, Color::EWhite));
  m = analyser.createMove(csBlackE3C1_G1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_G1, m.to());

  CoordSequence csWhiteD6F8_B8(cWhiteStartD6, cWhiteJumpF8);
  csWhiteD6F8_B8.append(cWhiteJumpH6);
  csWhiteD6F8_B8.append(cWhiteJumpF4);
  csWhiteD6F8_B8.append(cWhiteStartD6);
  csWhiteD6F8_B8.append(cWhiteJumpB8);

  Board bWhiteD6F8_B8;
  bWhiteD6F8_B8.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_B8.put(Draught(cBlackG3, Color::EBlack));
  bWhiteD6F8_B8.put(Draught(cWhiteJumpB8, Color::EWhite, true));
  bWhiteD6F8_B8.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_B8.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteD2, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteF2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F8_B8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_B8, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpGetKing()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpB8('b', '8');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF6('f', '6');
  const Coord cBlackJumpF8('f', '8');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpC1('c', '1');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpG3('g', '3');
  const Coord cWhiteJumpG1('g', '1');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D8(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D8.append(cBlackJumpD8);
  Board bBlackD4B6_D8;
  bBlackD4B6_D8.put(Draught(cBlackJumpD8, Color::EBlack, true));
  bBlackD4B6_D8.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cBlackF2, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cWhiteStartE5, Color::EWhite));
  bBlackD4B6_D8.put(Draught(cWhiteE7, Color::EWhite));
  m = analyser.createMove(csBlackD4B6_D8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4B6_D8, m.to());

  CoordSequence csBlackD4F6_D8(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_D8.append(cBlackJumpD8);
  Board bBlackD4F6_D8;
  bBlackD4F6_D8.put(Draught(cBlackJumpD8, Color::EBlack, true));
  bBlackD4F6_D8.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cBlackF2, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cWhiteC5, Color::EWhite));
  bBlackD4F6_D8.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csBlackD4F6_D8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4F6_D8, m.to());

  CoordSequence csBlackF4D6_B8(cBlackF4, cBlackJumpD6);
  csBlackF4D6_B8.append(cBlackJumpB8);
  Board bBlackF4D6_B8;
  bBlackF4D6_B8.put(Draught(cBlackJumpB8, Color::EBlack, true));
  bBlackF4D6_B8.put(Draught(cBlackD2, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cBlackStartD4, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cBlackF2, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cWhiteE7, Color::EWhite));
  bBlackF4D6_B8.put(Draught(cWhiteC5, Color::EWhite));
  m = analyser.createMove(csBlackF4D6_B8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackF4D6_B8, m.to());

  CoordSequence csBlackF4D6_F8(cBlackF4, cBlackJumpD6);
  csBlackF4D6_F8.append(cBlackJumpF8);
  Board bBlackF4D6_F8;
  bBlackF4D6_F8.put(Draught(cBlackJumpF8, Color::EBlack, true));
  bBlackF4D6_F8.put(Draught(cBlackD2, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cBlackStartD4, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cBlackF2, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cWhiteC5, Color::EWhite));
  bBlackF4D6_F8.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csBlackF4D6_F8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackF4D6_F8, m.to());

  CoordSequence csWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E1.append(cWhiteJumpE1);
  Board bWhiteE5C3_E1;
  bWhiteE5C3_E1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteE5C3_E1.put(Draught(cBlackF2, Color::EBlack));
  bWhiteE5C3_E1.put(Draught(cWhiteJumpE1, Color::EWhite, true));
  bWhiteE5C3_E1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5C3_E1.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5C3_E1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteE5C3_E1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5C3_E1, m.to());

  CoordSequence csWhiteE5G3_E1(cWhiteStartE5, cWhiteJumpG3);
  csWhiteE5G3_E1.append(cWhiteJumpE1);
  Board bWhiteE5G3_E1;
  bWhiteE5G3_E1.put(Draught(cBlackStartD4, Color::EBlack));
  bWhiteE5G3_E1.put(Draught(cBlackD2, Color::EBlack));
  bWhiteE5G3_E1.put(Draught(cWhiteJumpE1, Color::EWhite, true));
  bWhiteE5G3_E1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5G3_E1.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5G3_E1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteE5G3_E1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5G3_E1, m.to());

  CoordSequence csWhiteC5E3_C1(cWhiteC5, cWhiteJumpE3);
  csWhiteC5E3_C1.append(cWhiteJumpC1);
  Board bWhiteC5E3_C1;
  bWhiteC5E3_C1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteC5E3_C1.put(Draught(cBlackF2, Color::EBlack));
  bWhiteC5E3_C1.put(Draught(cWhiteJumpC1, Color::EWhite, true));
  bWhiteC5E3_C1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteC5E3_C1.put(Draught(cWhiteStartE5, Color::EWhite));
  bWhiteC5E3_C1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteC5E3_C1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteC5E3_C1, m.to());

  CoordSequence csWhiteC5E3_G1(cWhiteC5, cWhiteJumpE3);
  csWhiteC5E3_G1.append(cWhiteJumpG1);
  Board bWhiteC5E3_G1;
  bWhiteC5E3_G1.put(Draught(cBlackD2, Color::EBlack));
  bWhiteC5E3_G1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteC5E3_G1.put(Draught(cWhiteJumpG1, Color::EWhite, true));
  bWhiteC5E3_G1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteC5E3_G1.put(Draught(cWhiteStartE5, Color::EWhite));
  bWhiteC5E3_G1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteC5E3_G1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteC5E3_G1, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpNoRequestedDraught()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackJumpB8('b', '8');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF4('f', '4');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));

  Move mBlackF4D6_B8(cBlackJumpF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_B8.append(cBlackJumpB8);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6_B8, Move::ErrorNoRequestedDraught);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpNothingToJumpOver()
{
  const Coord cBlackStartF4('f', '4');
  const Coord cBlackJumpB8('b', '8');
  const Coord cBlackJumpD6('d', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');

  Board b;
  b.put(Draught(cBlackStartF4, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));

  Move mBlackF4D6_B8(cBlackStartF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_B8.append(cBlackJumpB8);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6_B8, Move::ErrorNothingToJumpOver);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpInWrongDirection()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackJumpB4('b', '4');
  const Coord cBlackJumpD6('d', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpG5('g', '5');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));

  Move mBlackF4D6_B4(cBlackF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_B4.append(cBlackJumpB4);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6_B4, Move::ErrorInWrongDirection);

  Move mWhiteC5E3_G5(cWhiteC5, cWhiteJumpE3, Move::EJump);
  mWhiteC5E3_G5.append(cWhiteJumpG5);
  CPPUNIT_ASSERT_THROW(b + mWhiteC5E3_G5, Move::ErrorInWrongDirection);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpToBusySquare()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackF8('f', '8');
  const Coord cBlackC1('c', '1');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD6('d', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteD8('d', '8');
  const Coord cWhiteE1('e', '1');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE3('e', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cBlackC1, Color::EBlack));
  b.put(Draught(cBlackF8, Color::EBlack, true));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));
  b.put(Draught(cWhiteD8, Color::EWhite));
  b.put(Draught(cWhiteE1, Color::EWhite, true));

  Move mBlackD4B6_D8(cBlackStartD4, cBlackJumpB6, Move::EJump);
  mBlackD4B6_D8.append(cWhiteD8);
  CPPUNIT_ASSERT_THROW(b + mBlackD4B6_D8, Move::ErrorToBusySquare);

  Move mBlackF4D6_F8(cBlackF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_F8.append(cBlackF8);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6_F8, Move::ErrorToBusySquare);

  Move mWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3, Move::EJump);
  mWhiteE5C3_E1.append(cWhiteE1);
  CPPUNIT_ASSERT_THROW(b + mWhiteE5C3_E1, Move::ErrorToBusySquare);

  Move mWhiteC5E3_C1(cWhiteC5, cWhiteJumpE3, Move::EJump);
  mWhiteC5E3_C1.append(cBlackC1);
  CPPUNIT_ASSERT_THROW(b + mWhiteC5E3_C1, Move::ErrorToBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpOverBusySquare()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackF8('f', '8');
  const Coord cBlackC1('c', '1');
  const Coord cBlackB4('b', '4');
  const Coord cBlackB2('b', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF6('f', '6');
  const Coord cBlackJumpH6('h', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteD8('d', '8');
  const Coord cWhiteE1('e', '1');
  const Coord cWhiteA5('a', '5');
  const Coord cWhiteG7('g', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpA3('a', '3');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack, true));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cBlackC1, Color::EBlack));
  b.put(Draught(cBlackB2, Color::EBlack));
  b.put(Draught(cBlackB4, Color::EBlack));
  b.put(Draught(cBlackF8, Color::EBlack, true));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite, true));
  b.put(Draught(cWhiteC7, Color::EWhite));
  b.put(Draught(cWhiteD8, Color::EWhite));
  b.put(Draught(cWhiteE1, Color::EWhite, true));
  b.put(Draught(cWhiteA5, Color::EWhite, true));
  b.put(Draught(cWhiteG7, Color::EWhite, true));

  Move mBlackD4F6_B6(cBlackStartD4, cBlackJumpF6, Move::EJump);
  mBlackD4F6_B6.append(cWhiteD8);
  mBlackD4F6_B6.append(cBlackJumpB6);
  CPPUNIT_ASSERT_THROW(b + mBlackD4F6_B6, Move::ErrorJumpOverBusySquare);

  Move mBlackF4D6_H6(cBlackF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_H6.append(cBlackF8);
  mBlackF4D6_H6.append(cBlackJumpH6);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6_H6, Move::ErrorJumpOverBusySquare);

  Move mWhiteA5C3_G3(cWhiteA5, cWhiteJumpC3, Move::EJump);
  mWhiteA5C3_G3.append(cWhiteE1);
  mWhiteA5C3_G3.append(cWhiteJumpG3);
  CPPUNIT_ASSERT_THROW(b + mWhiteA5C3_G3, Move::ErrorJumpOverBusySquare);

  Move mWhiteC5A3_E3(cWhiteC5, cWhiteJumpA3, Move::EJump);
  mWhiteC5A3_E3.append(cBlackC1);
  mWhiteC5A3_E3.append(cWhiteJumpE3);
  CPPUNIT_ASSERT_THROW(b + mWhiteC5A3_E3, Move::ErrorJumpOverBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpMoreJumpExist()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF6('f', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite, true));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  Move mBlackD4B6_D8(cBlackStartD4, cBlackJumpB6, Move::EJump);
  mBlackD4B6_D8.append(cBlackJumpD8);
  CPPUNIT_ASSERT_THROW(b + mBlackD4B6_D8, Move::ErrorJumpExist);

  Move mBlackD4F6_D8(cBlackStartD4, cBlackJumpF6, Move::EJump);
  mBlackD4F6_D8.append(cBlackJumpD8);
  CPPUNIT_ASSERT_THROW(b + mBlackD4F6_D8, Move::ErrorJumpExist);

  Move mBlackF4D6(cBlackF4, cBlackJumpD6, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6, Move::ErrorJumpExist);

  Move mWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3, Move::EJump);
  mWhiteE5C3_E1.append(cWhiteJumpE1);
  CPPUNIT_ASSERT_THROW(b + mWhiteE5C3_E1, Move::ErrorJumpExist);

  Move mWhiteE5G3_E1(cWhiteStartE5, cWhiteJumpG3, Move::EJump);
  mWhiteE5G3_E1.append(cWhiteJumpE1);
  CPPUNIT_ASSERT_THROW(b + mWhiteE5G3_E1, Move::ErrorJumpExist);

  Move mWhiteC5E3(cWhiteC5, cWhiteJumpE3, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteC5E3, Move::ErrorJumpExist);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpNotTerminatedAfterGetKing()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpF6('f', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  Move mBlackD4B6_D4(cBlackStartD4, cBlackJumpB6, Move::EJump);
  mBlackD4B6_D4.append(cBlackJumpD8);
  mBlackD4B6_D4.append(cBlackJumpF6);
  mBlackD4B6_D4.append(cBlackStartD4);
  CPPUNIT_ASSERT_THROW(b + mBlackD4B6_D4, Move::ErrorGetKingButMoveFurther);

  Move mBlackD4F6_D4(cBlackStartD4, cBlackJumpF6, Move::EJump);
  mBlackD4F6_D4.append(cBlackJumpD8);
  mBlackD4F6_D4.append(cBlackJumpB6);
  mBlackD4F6_D4.append(cBlackStartD4);
  CPPUNIT_ASSERT_THROW(b + mBlackD4F6_D4, Move::ErrorGetKingButMoveFurther);

  Move mWhiteE5C3_E5(cWhiteStartE5, cWhiteJumpC3, Move::EJump);
  mWhiteE5C3_E5.append(cWhiteJumpE1);
  mWhiteE5C3_E5.append(cWhiteJumpG3);
  mWhiteE5C3_E5.append(cWhiteStartE5);
  CPPUNIT_ASSERT_THROW(b + mWhiteE5C3_E5, Move::ErrorGetKingButMoveFurther);

  Move mWhiteE5G3_E5(cWhiteStartE5, cWhiteJumpG3, Move::EJump);
  mWhiteE5G3_E5.append(cWhiteJumpE1);
  mWhiteE5G3_E5.append(cWhiteJumpC3);
  mWhiteE5G3_E5.append(cWhiteStartE5);
  CPPUNIT_ASSERT_THROW(b + mWhiteE5G3_E5, Move::ErrorGetKingButMoveFurther);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpOverSameColor()
{
  const Coord cBlackStartF4('f', '4');
  const Coord cBlackD4('d', '4');
  const Coord cBlackC7('c', '7');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpB8('b', '8');

  const Coord cWhiteStartC5('c', '5');
  const Coord cWhiteE5('e', '5');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpC1('c', '1');

  Board b;
  b.put(Draught(cBlackStartF4, Color::EBlack));
  b.put(Draught(cBlackD4, Color::EBlack));
  b.put(Draught(cBlackC7, Color::EBlack));
  b.put(Draught(cWhiteStartC5, Color::EWhite));
  b.put(Draught(cWhiteE5, Color::EWhite));
  b.put(Draught(cWhiteD2, Color::EWhite));

  Move mBlackF4D6_B8(cBlackStartF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_B8.append(cBlackJumpB8);
  CPPUNIT_ASSERT_THROW(b + mBlackF4D6_B8, Move::ErrorJumpOverSameColor);

  Move mWhiteC5E3_C1(cWhiteStartC5, cWhiteJumpE3, Move::EJump);
  mWhiteC5E3_C1.append(cWhiteJumpC1);
  CPPUNIT_ASSERT_THROW(b + mWhiteC5E3_C1, Move::ErrorJumpOverSameColor);
}

void AmericanCheckersPositionAnalyserTests::createMoveFromTwoBoardsBlack()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::createMoveFromTwoBoardsWhite()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void AmericanCheckersPositionAnalyserTests::createMoveFromTwoBoardsNotFound()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}
