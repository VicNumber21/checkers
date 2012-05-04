#include "MoveTests.h"
#include "Move.h"
#include "Board.h"
#include "Draught.h"
#include "Color.h"
#include "Coord.h"
#include "FramedBoardView.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( MoveTests );


std::ostream & operator<<(std::ostream &aOut, const Board &aBoard)
{
  Checkers::ConsoleUi::FramedBoardView view(aBoard);
  return aOut << std::endl << view;
}

void MoveTests::setUp()
{
}

void MoveTests::tearDown()
{
}

void MoveTests::undefinedUsage()
{
  Move m;
  CPPUNIT_ASSERT_THROW(m.append(Coord('a', '1')), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m.score(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m.begin(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m.end(), Move::ErrorUndefinedUsage);
}

void MoveTests::unexpectedAppend()
{
  Move m(Coord('a', '1'), Coord('b', '2'));
  CPPUNIT_ASSERT_THROW(m.append(Coord('c', '3')), Move::ErrorUnexpectedAppend);
}

void MoveTests::wrongSequenceForSimpleMove()
{
  CPPUNIT_ASSERT_THROW(Move m(Coord('a', '5'), Coord('b', '2')), Move::ErrorCoordSequence);
  CPPUNIT_ASSERT_THROW(Move m(Coord('a', '1'), Coord('c', '3')), Move::ErrorCoordSequence);
  CPPUNIT_ASSERT_THROW(Move m(Coord('a', '2'), Coord('b', '3')), Move::ErrorCoordSequence);
}

void MoveTests::wrongSequenceForJump()
{
  CPPUNIT_ASSERT_THROW(Move m1(Coord('a', '1'), Coord('b', '2'), Move::EJump), Move::ErrorCoordSequence);

  Move m2(Coord('f', '2'), Coord('d', '4'), Move::EJump);
  CPPUNIT_ASSERT_THROW(m2.append(Coord('e', '5')), Move::ErrorCoordSequence);

  Move m3(Coord('f', '2'), Coord('d', '4'), Move::EJump);
  CPPUNIT_ASSERT_THROW(m3.append(Coord('f', '2')), Move::ErrorCoordSequence);
}

void MoveTests::equal()
{
  Move m1;
  Move m2;
  Move m3(Coord('h', '8'), Coord('f', '6'), Move::EJump);
  Move m4(Coord('f', '6'), Coord('g', '5'));
  CPPUNIT_ASSERT(m1 == m2);
  CPPUNIT_ASSERT(!(m1 == m3));
  CPPUNIT_ASSERT(!(m1 == m4));

  m1 = Move(Coord('a', '3'), Coord('b', '4'));
  m2 = Move(Coord('a', '3'), Coord('b', '4'));
  CPPUNIT_ASSERT(m1 == m2);
  CPPUNIT_ASSERT(!(m1 == m3));
  CPPUNIT_ASSERT(!(m1 == m4));

  m1 = Move(Coord('c', '5'), Coord('a', '3'), Move::EJump);
  m2 = Move(Coord('c', '5'), Coord('a', '3'), Move::EJump);
  CPPUNIT_ASSERT(m1 == m2);
  CPPUNIT_ASSERT(!(m1 == m3));
  CPPUNIT_ASSERT(!(m1 == m4));

  m1.append(Coord('c', '1'));
  m2.append(Coord('c', '1'));
  CPPUNIT_ASSERT(m1 == m2);
  CPPUNIT_ASSERT(!(m1 == m3));
  CPPUNIT_ASSERT(!(m1 == m4));

  m2.append(Coord('e', '3'));
  CPPUNIT_ASSERT(!(m1 == m2));
}

void MoveTests::notEqual()
{
  Move m1;
  Move m2;
  Move m3(Coord('h', '8'), Coord('f', '6'), Move::EJump);
  Move m4(Coord('f', '6'), Coord('g', '5'));
  CPPUNIT_ASSERT(!(m1 != m2));
  CPPUNIT_ASSERT(m1 != m3);
  CPPUNIT_ASSERT(m1 != m4);

  m1 = Move(Coord('a', '3'), Coord('b', '4'));
  m2 = Move(Coord('a', '3'), Coord('b', '4'));
  CPPUNIT_ASSERT(!(m1 != m2));
  CPPUNIT_ASSERT(m1 != m3);
  CPPUNIT_ASSERT(m1 != m4);

  m1 = Move(Coord('c', '5'), Coord('a', '3'), Move::EJump);
  m2 = Move(Coord('c', '5'), Coord('a', '3'), Move::EJump);
  CPPUNIT_ASSERT(!(m1 != m2));
  CPPUNIT_ASSERT(m1 != m3);
  CPPUNIT_ASSERT(m1 != m4);

  m1.append(Coord('c', '1'));
  m2.append(Coord('c', '1'));
  CPPUNIT_ASSERT(!(m1 != m2));
  CPPUNIT_ASSERT(m1 != m3);
  CPPUNIT_ASSERT(m1 != m4);

  m2.append(Coord('e', '3'));
  CPPUNIT_ASSERT(m1 != m2);
}

void MoveTests::type()
{
  Move m1;
  CPPUNIT_ASSERT_EQUAL(Move::EUndefined, m1.type());

  Move m2(Coord('b', '6'), Coord('c', '7'));
  CPPUNIT_ASSERT_EQUAL(Move::ESimple, m2.type());

  Move m3(Coord('d', '4'), Coord('f', '6'), Move::EJump);
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m3.type());
}

void MoveTests::simpleMoveScore()
{
  Move m(Coord('b', '6'), Coord('c', '7'));
  CPPUNIT_ASSERT_EQUAL(0, m.score());
}

void MoveTests::simpleJumpScore()
{
  Move m(Coord('d', '4'), Coord('f', '6'), Move::EJump);
  CPPUNIT_ASSERT_EQUAL(1, m.score());
}

void MoveTests::complexJumpScore()
{
  Move m(Coord('d', '4'), Coord('f', '6'), Move::EJump);
  m.append(Coord('h', '4'));
  CPPUNIT_ASSERT_EQUAL(2, m.score());

  m.append(Coord('f', '2'));
  CPPUNIT_ASSERT_EQUAL(3, m.score());

  m.append(Coord('d', '4'));
  CPPUNIT_ASSERT_EQUAL(4, m.score());

  m.append(Coord('b', '6'));
  CPPUNIT_ASSERT_EQUAL(5, m.score());

}

void MoveTests::boardPlusSimpleMove()
{
  const Coord cWhiteStart('c', '3');
  const Coord cWhiteLeftForward('b', '4');
  const Coord cWhiteRightForward('d', '4');

  const Coord cBlackStart('f', '6');
  const Coord cBlackLeftForward('g', '5');
  const Coord cBlackRightForward('e', '5');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cBlackStart, Color::EBlack));

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);
}

void MoveTests::boardPlusSimpleMoveByKing()
{
  const Coord cWhiteStart('c', '3');
  const Coord cWhiteLeftForward('b', '4');
  const Coord cWhiteRightForward('d', '4');
  const Coord cWhiteLeftBack('b', '2');
  const Coord cWhiteRightBack('d', '2');

  const Coord cBlackStart('f', '6');
  const Coord cBlackLeftForward('g', '5');
  const Coord cBlackRightForward('e', '5');
  const Coord cBlackLeftBack('g', '7');
  const Coord cBlackRightBack('e', '7');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cBlackStart, Color::EBlack, true));

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, b + mWhiteLeftBack);

  Move mWhiteRightBack(cWhiteStart, cWhiteRightBack);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, b + mWhiteRightBack);

  Move mBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackRightBack(cBlackStart, cBlackRightBack);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, b + mBlackRightBack);

  Move mBlackLeftBack(cBlackStart, cBlackLeftBack);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, b + mBlackLeftBack);
}

void MoveTests::boardPlusSimpleMoveGetKing()
{
  const Coord cWhiteStart('c', '7');
  const Coord cWhiteLeftForward('b', '8');
  const Coord cWhiteRightForward('d', '8');

  const Coord cBlackStart('f', '2');
  const Coord cBlackLeftForward('g', '1');
  const Coord cBlackRightForward('e', '1');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cBlackStart, Color::EBlack));

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);
}

void MoveTests::boardPlusSimpleMoveNoRequestedDraught()
{
  const Coord cWhiteStart('c', '5');
  const Coord cWhiteWrongStart('e', '5');
  const Coord cWhiteMoveTo('d', '6');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite));

  Move mWhite(cWhiteWrongStart, cWhiteMoveTo);
  CPPUNIT_ASSERT_THROW(b + mWhite, Move::ErrorNoRequestedDraught);
}

void MoveTests::boardPlusSimpleMoveInWrongDirection()
{
  const Coord cWhiteStart('c', '7');
  const Coord cWhiteLeftBack('b', '6');
  const Coord cWhiteRightBack('d', '6');

  const Coord cBlackStart('f', '2');
  const Coord cBlackLeftBack('g', '3');
  const Coord cBlackRightBack('e', '3');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cBlackStart, Color::EBlack));

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftBack, Move::ErrorInWrongDirection);

  Move mWhiteRightBack(cWhiteStart, cWhiteRightBack);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightBack, Move::ErrorInWrongDirection);

  Move mBlackRightBack(cBlackStart, cBlackRightBack);
  CPPUNIT_ASSERT_THROW(b + mBlackRightBack, Move::ErrorInWrongDirection);

  Move mBlackLeftBack(cBlackStart, cBlackLeftBack);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftBack, Move::ErrorInWrongDirection);
}

void MoveTests::boardPlusSimpleMoveToBusySquare()
{
  const Coord cWhiteStart('d', '4');
  const Coord cWhiteLeftForward('c', '5');

  const Coord cBlackStart('e', '5');
  const Coord cBlackLeftForward('f', '4');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  b.put(Draught(cBlackStart, Color::EBlack, true));
  b.put(Draught(cBlackLeftForward, Color::EBlack));

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftForward, Move::ErrorToBusySquare);

  Move mWhiteRightForward(cWhiteStart, cBlackStart);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightForward, Move::ErrorToBusySquare);

  Move mBlackRightForward(cBlackStart, cWhiteStart);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorToBusySquare);

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftForward, Move::ErrorToBusySquare);
}

void MoveTests::boardPlusSimpleMoveJumpExist()
{
  const Coord cWhiteStart('d', '4');
  const Coord cWhiteLeftForward('c', '5');

  const Coord cBlackStart('e', '5');
  const Coord cBlackLeftForward('f', '4');

  Board b;
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cBlackStart, Color::EBlack, true));

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftForward, Move::ErrorJumpExist);

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  CPPUNIT_ASSERT_THROW(b + mBlackLeftForward, Move::ErrorJumpExist);
}

void MoveTests::boardPlusSimpleJump()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpByKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpGetKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpNoRequestedDraught()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpInWrongDirection()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpToBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpMoreJumpExist()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleJumpOverSameColor()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJump()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpByKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpGetKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpNoRequestedDraught()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpInWrongDirection()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpToBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpOverBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpMoreJumpExist()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpNotTerminatedAfterGetKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusComplexJumpOverSameColor()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMove()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMoveByKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMoveLoseKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMoveNoRequestedDraught()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMoveInWrongDirection()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMoveToBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleMoveJumpExist()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJump()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpByKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpLoseKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpNoRequestedDraught()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpInWrongDirection()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpToBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpMoreJumpExist()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusSimpleJumpOverSameColor()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJump()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpByKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpLoseKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpNoRequestedDraught()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpInWrongDirection()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpToBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpOverBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpMoreJumpExist()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpNotTerminatedAfterGetKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusComplexJumpOverSameColor()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusPlusMoveToGetTheSameBoard()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusMinusMoveToGetTheSameBoard()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusBoard()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusMoveNotFound()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}
