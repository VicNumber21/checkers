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
  const Coord cBlackStart('c', '3');
  const Coord cBlackLeftForward('b', '4');
  const Coord cBlackRightForward('d', '4');

  const Coord cWhiteStart('f', '6');
  const Coord cWhiteLeftForward('g', '5');
  const Coord cWhiteRightForward('e', '5');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);
}

void MoveTests::boardPlusSimpleMoveByKing()
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

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mBlackLeftBack(cBlackStart, cBlackLeftBack);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, b + mBlackLeftBack);

  Move mBlackRightBack(cBlackStart, cBlackRightBack);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, b + mBlackRightBack);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);

  Move mWhiteRightBack(cWhiteStart, cWhiteRightBack);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, b + mWhiteRightBack);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, b + mWhiteLeftBack);
}

void MoveTests::boardPlusSimpleMoveGetKing()
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

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);
}

void MoveTests::boardPlusSimpleMoveNoRequestedDraught()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackWrongStart('e', '5');
  const Coord cBlackMoveTo('d', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));

  Move mBlack(cBlackWrongStart, cBlackMoveTo);
  CPPUNIT_ASSERT_THROW(b + mBlack, Move::ErrorNoRequestedDraught);
}

void MoveTests::boardPlusSimpleMoveInWrongDirection()
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

void MoveTests::boardPlusSimpleMoveToBusySquare()
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

void MoveTests::boardPlusSimpleMoveJumpExist()
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

void MoveTests::boardPlusSimpleJump()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack('f', '4');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite('c', '5');
  const Coord cWhiteLeftForward('c', '3');
  const Coord cWhiteRightForward('g', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward, Move::EJump);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward, Move::EJump);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward, Move::EJump);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward, Move::EJump);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);
}

void MoveTests::boardPlusSimpleJumpByKing()
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

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward, Move::EJump);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite3, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackLeftBack(cBlackStart, cBlackLeftBack, Move::EJump);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterBlackLeftBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, b + mBlackLeftBack);

  Move mBlackRightBack(cBlackStart, cBlackRightBack, Move::EJump);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackRightBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterBlackRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, b + mBlackRightBack);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward, Move::EJump);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite3, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);

  Move mWhiteRightBack(cWhiteStart, cWhiteRightBack, Move::EJump);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteRightBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, b + mWhiteRightBack);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack, Move::EJump);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, b + mWhiteLeftBack);
}

void MoveTests::boardPlusSimpleJumpGetKing()
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

  Move mBlackLeftForward(cBlackStart, cBlackLeftForward, Move::EJump);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, b + mBlackLeftForward);

  Move mBlackRightForward(cBlackStart, cBlackRightForward, Move::EJump);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackRightForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, b + mBlackRightForward);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward, Move::EJump);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite2, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, b + mWhiteRightForward);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward, Move::EJump);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, b + mWhiteLeftForward);
}

void MoveTests::boardPlusSimpleJumpNoRequestedDraught()
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

void MoveTests::boardPlusSimpleJumpInWrongDirection()
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

void MoveTests::boardPlusSimpleJumpToBusySquare()
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

  Move mBlackRightForward(cBlackStart, cWhiteStart, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorToBusySquare);

  Move mWhiteRightForward(cWhiteStart, cBlackStart, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteRightForward, Move::ErrorToBusySquare);

  Move mWhiteLeftForward(cWhiteStart, cWhiteLeftForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mWhiteLeftForward, Move::ErrorToBusySquare);
}

void MoveTests::boardPlusSimpleJumpMoreJumpExist()
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

void MoveTests::boardPlusSimpleJumpOverSameColor()
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

/* TODO Remove if not needed
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
*/

void MoveTests::boardMinusBoard()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardMinusMoveNotFound()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}
