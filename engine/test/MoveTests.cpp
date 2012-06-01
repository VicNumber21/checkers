#include "MoveTests.h"
#include "Move.h"
#include "Board.h"
#include "Draught.h"
#include "Color.h"
#include "Coord.h"
#include "PrettyPrint.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( MoveTests );


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
  CPPUNIT_ASSERT_THROW(m.coords(), Move::ErrorUndefinedUsage);
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
  CPPUNIT_ASSERT(!(m1 == m2));
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
  CPPUNIT_ASSERT(m1 != m2);
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
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteRightForward('c', '3');

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
  bAfterWhiteRightBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, b + mWhiteRightBack);

  Move mWhiteLeftBack(cWhiteStart, cWhiteLeftBack, Move::EJump);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack3, Color::EBlack));
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

void MoveTests::boardPlusSimpleJumpNothingToJumpOver()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackMoveTo('e', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  Move mBlack(cBlackStart, cBlackMoveTo, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlack, Move::ErrorNothingToJumpOver);
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

  Move mBlackRightForward(cBlackStart, cBlackRightForward, Move::EJump);
  CPPUNIT_ASSERT_THROW(b + mBlackRightForward, Move::ErrorToBusySquare);

  Move mWhiteRightForward(cWhiteStart, cWhiteRightForward, Move::EJump);
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

  Move mBlackAtTheEndLeftForward(cBlackStart, cBlackJump1, Move::EJump);
  mBlackAtTheEndLeftForward.append(cBlackJump2);
  Move mBlackAtTheEndRightForward(mBlackAtTheEndLeftForward);
  mBlackAtTheEndLeftForward.append(cBlackJump3LeftForward);
  mBlackAtTheEndRightForward.append(cBlackJump3RightForward);

  Board bBlackAtTheEndLeftForward;
  bBlackAtTheEndLeftForward.put(Draught(cBlackJump3LeftForward, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack3, Color::EBlack, true));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack4, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  CPPUNIT_ASSERT_EQUAL(bBlackAtTheEndLeftForward, b + mBlackAtTheEndLeftForward);

  Board bBlackAtTheEndRightForward;
  bBlackAtTheEndRightForward.put(Draught(cBlackJump3RightForward, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack3, Color::EBlack, true));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack4, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bBlackAtTheEndRightForward.put(Draught(cAnotherWhite1, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackAtTheEndRightForward, b + mBlackAtTheEndRightForward);

  Move mWhiteAtTheEndLeftForward(cWhiteStart, cWhiteJump1, Move::EJump);
  mWhiteAtTheEndLeftForward.append(cWhiteJump2);
  Move mWhiteAtTheEndRightForward(mWhiteAtTheEndLeftForward);
  mWhiteAtTheEndLeftForward.append(cWhiteJump3LeftForward);
  mWhiteAtTheEndRightForward.append(cWhiteJump3RightForward);

  Board bWhiteAtTheEndLeftForward;
  bWhiteAtTheEndLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bWhiteAtTheEndLeftForward.put(Draught(cWhiteJump3LeftForward, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite3, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite4, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteAtTheEndLeftForward, b + mWhiteAtTheEndLeftForward);

  Board bWhiteAtTheEndRightForward;
  bWhiteAtTheEndRightForward.put(Draught(cBlackStart, Color::EBlack));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bWhiteAtTheEndRightForward.put(Draught(cWhiteJump3RightForward, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite3, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite4, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteAtTheEndRightForward, b + mWhiteAtTheEndRightForward);
}

void MoveTests::boardPlusComplexJumpByKing()
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

  Move mBlackE3C1_E3(cBlackStartE3, cBlackJumpC1, Move::EJump);
  mBlackE3C1_E3.append(cBlackJumpA3);
  mBlackE3C1_E3.append(cBlackJumpC5);
  Move mBlackE3C1_A7(mBlackE3C1_E3);
  mBlackE3C1_E3.append(cBlackStartE3);
  mBlackE3C1_A7.append(cBlackJumpA7);

  Board bBlackE3C1_E3;
  bBlackE3C1_E3.put(Draught(cBlackStartE3, Color::EBlack, true));
  bBlackE3C1_E3.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_E3.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_E3.put(Draught(cWhiteB6, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_E3, b + mBlackE3C1_E3);

  Board bBlackE3C1_A7;
  bBlackE3C1_A7.put(Draught(cBlackJumpA7, Color::EBlack, true));
  bBlackE3C1_A7.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_A7.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_A7.put(Draught(cWhiteD4, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_A7, b + mBlackE3C1_A7);

  Move mBlackE3C5_E3(cBlackStartE3, cBlackJumpC5, Move::EJump);
  Move mBlackE3C5_A7(mBlackE3C5_E3);
  mBlackE3C5_E3.append(cBlackJumpA3);
  mBlackE3C5_E3.append(cBlackJumpC1);
  mBlackE3C5_E3.append(cBlackStartE3);
  mBlackE3C5_A7.append(cBlackJumpA7);

  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_E3, b + mBlackE3C5_E3); //the same board as jump in another direction

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
  CPPUNIT_ASSERT_EQUAL(bBlackE3C5_A7, b + mBlackE3C5_A7);

  Move mWhiteD6F8_D6(cWhiteStartD6, cWhiteJumpF8, Move::EJump);
  mWhiteD6F8_D6.append(cWhiteJumpH6);
  mWhiteD6F8_D6.append(cWhiteJumpF4);
  Move mWhiteD6F8_H2(mWhiteD6F8_D6);
  mWhiteD6F8_D6.append(cWhiteStartD6);
  mWhiteD6F8_H2.append(cWhiteJumpH2);

  Board bWhiteD6F8_D6;
  bWhiteD6F8_D6.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_D6.put(Draught(cBlackG3, Color::EBlack));
  bWhiteD6F8_D6.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bWhiteD6F8_D6.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_D6.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteD2, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_D6, b + mWhiteD6F8_D6);

  Board bWhiteD6F8_H2;
  bWhiteD6F8_H2.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_H2.put(Draught(cBlackE5, Color::EBlack));
  bWhiteD6F8_H2.put(Draught(cWhiteJumpH2, Color::EWhite, true));
  bWhiteD6F8_H2.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_H2.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteD2, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_H2, b + mWhiteD6F8_H2);

  Move mWhiteD6F4_D6(cWhiteStartD6, cWhiteJumpF4, Move::EJump);
  Move mWhiteD6F4_H2(mWhiteD6F4_D6);
  mWhiteD6F4_D6.append(cWhiteJumpH6);
  mWhiteD6F4_D6.append(cWhiteJumpF8);
  mWhiteD6F4_D6.append(cWhiteStartD6);
  mWhiteD6F4_H2.append(cWhiteJumpH2);

  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_D6, b + mWhiteD6F4_D6); //the same board as jump in another direction

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
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F4_H2, b + mWhiteD6F4_H2);
}

void MoveTests::boardPlusComplexJumpByKingOverKingRow()
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

  Move mBlackD4B6_D4(cBlackStartD4, cBlackJumpB6, Move::EJump);
  mBlackD4B6_D4.append(cBlackJumpD8);
  mBlackD4B6_D4.append(cBlackJumpF6);
  mBlackD4B6_D4.append(cBlackStartD4);
  Board bBlackD4_D4;
  bBlackD4_D4.put(Draught(cBlackStartD4, Color::EBlack, true));
  bBlackD4_D4.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4_D4.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4_D4.put(Draught(cBlackF2, Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(bBlackD4_D4, b + mBlackD4B6_D4);

  Move mBlackD4F6_D4(cBlackStartD4, cBlackJumpF6, Move::EJump);
  mBlackD4F6_D4.append(cBlackJumpD8);
  mBlackD4F6_D4.append(cBlackJumpB6);
  mBlackD4F6_D4.append(cBlackStartD4);
  CPPUNIT_ASSERT_EQUAL(bBlackD4_D4, b + mBlackD4F6_D4);

  Move mWhiteE5C3_E5(cWhiteStartE5, cWhiteJumpC3, Move::EJump);
  mWhiteE5C3_E5.append(cWhiteJumpE1);
  mWhiteE5C3_E5.append(cWhiteJumpG3);
  mWhiteE5C3_E5.append(cWhiteStartE5);
  Board bWhiteE5_E5;
  bWhiteE5_E5.put(Draught(cWhiteStartE5, Color::EWhite, true));
  bWhiteE5_E5.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5_E5.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5_E5.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteE5_E5, b + mWhiteE5C3_E5);

  Move mWhiteE5G3_E5(cWhiteStartE5, cWhiteJumpG3, Move::EJump);
  mWhiteE5G3_E5.append(cWhiteJumpE1);
  mWhiteE5G3_E5.append(cWhiteJumpC3);
  mWhiteE5G3_E5.append(cWhiteStartE5);
  CPPUNIT_ASSERT_EQUAL(bWhiteE5_E5, b + mWhiteE5G3_E5);
}
void MoveTests::boardPlusComplexJumpByKingOverStartSquare()
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

  Move mBlackE3C1_G1(cBlackStartE3, cBlackJumpC1, Move::EJump);
  mBlackE3C1_G1.append(cBlackJumpA3);
  mBlackE3C1_G1.append(cBlackJumpC5);
  mBlackE3C1_G1.append(cBlackStartE3);
  mBlackE3C1_G1.append(cBlackJumpG1);

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
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_G1, b + mBlackE3C1_G1);

  Move mWhiteD6F8_B8(cWhiteStartD6, cWhiteJumpF8, Move::EJump);
  mWhiteD6F8_B8.append(cWhiteJumpH6);
  mWhiteD6F8_B8.append(cWhiteJumpF4);
  mWhiteD6F8_B8.append(cWhiteStartD6);
  mWhiteD6F8_B8.append(cWhiteJumpB8);

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
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_B8, b + mWhiteD6F8_B8);
}

void MoveTests::boardPlusComplexJumpGetKing()
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

  Move mBlackD4B6_D8(cBlackStartD4, cBlackJumpB6, Move::EJump);
  mBlackD4B6_D8.append(cBlackJumpD8);
  Board bBlackD4B6_D8;
  bBlackD4B6_D8.put(Draught(cBlackJumpD8, Color::EBlack, true));
  bBlackD4B6_D8.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cBlackF2, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cWhiteStartE5, Color::EWhite));
  bBlackD4B6_D8.put(Draught(cWhiteE7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackD4B6_D8, b + mBlackD4B6_D8);

  Move mBlackD4F6_D8(cBlackStartD4, cBlackJumpF6, Move::EJump);
  mBlackD4F6_D8.append(cBlackJumpD8);
  Board bBlackD4F6_D8;
  bBlackD4F6_D8.put(Draught(cBlackJumpD8, Color::EBlack, true));
  bBlackD4F6_D8.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cBlackF2, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cWhiteC5, Color::EWhite));
  bBlackD4F6_D8.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackD4F6_D8, b + mBlackD4F6_D8);

  Move mBlackF4D6_B8(cBlackF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_B8.append(cBlackJumpB8);
  Board bBlackF4D6_B8;
  bBlackF4D6_B8.put(Draught(cBlackJumpB8, Color::EBlack, true));
  bBlackF4D6_B8.put(Draught(cBlackD2, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cBlackStartD4, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cBlackF2, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cWhiteE7, Color::EWhite));
  bBlackF4D6_B8.put(Draught(cWhiteC5, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackF4D6_B8, b + mBlackF4D6_B8);

  Move mBlackF4D6_F8(cBlackF4, cBlackJumpD6, Move::EJump);
  mBlackF4D6_F8.append(cBlackJumpF8);
  Board bBlackF4D6_F8;
  bBlackF4D6_F8.put(Draught(cBlackJumpF8, Color::EBlack, true));
  bBlackF4D6_F8.put(Draught(cBlackD2, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cBlackStartD4, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cBlackF2, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cWhiteC5, Color::EWhite));
  bBlackF4D6_F8.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bBlackF4D6_F8, b + mBlackF4D6_F8);

  Move mWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3, Move::EJump);
  mWhiteE5C3_E1.append(cWhiteJumpE1);
  Board bWhiteE5C3_E1;
  bWhiteE5C3_E1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteE5C3_E1.put(Draught(cBlackF2, Color::EBlack));
  bWhiteE5C3_E1.put(Draught(cWhiteJumpE1, Color::EWhite, true));
  bWhiteE5C3_E1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5C3_E1.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5C3_E1.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteE5C3_E1, b + mWhiteE5C3_E1);

  Move mWhiteE5G3_E1(cWhiteStartE5, cWhiteJumpG3, Move::EJump);
  mWhiteE5G3_E1.append(cWhiteJumpE1);
  Board bWhiteE5G3_E1;
  bWhiteE5G3_E1.put(Draught(cBlackStartD4, Color::EBlack));
  bWhiteE5G3_E1.put(Draught(cBlackD2, Color::EBlack));
  bWhiteE5G3_E1.put(Draught(cWhiteJumpE1, Color::EWhite, true));
  bWhiteE5G3_E1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5G3_E1.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5G3_E1.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteE5G3_E1, b + mWhiteE5G3_E1);

  Move mWhiteC5E3_C1(cWhiteC5, cWhiteJumpE3, Move::EJump);
  mWhiteC5E3_C1.append(cWhiteJumpC1);
  Board bWhiteC5E3_C1;
  bWhiteC5E3_C1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteC5E3_C1.put(Draught(cBlackF2, Color::EBlack));
  bWhiteC5E3_C1.put(Draught(cWhiteJumpC1, Color::EWhite, true));
  bWhiteC5E3_C1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteC5E3_C1.put(Draught(cWhiteStartE5, Color::EWhite));
  bWhiteC5E3_C1.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteC5E3_C1, b + mWhiteC5E3_C1);

  Move mWhiteC5E3_G1(cWhiteC5, cWhiteJumpE3, Move::EJump);
  mWhiteC5E3_G1.append(cWhiteJumpG1);
  Board bWhiteC5E3_G1;
  bWhiteC5E3_G1.put(Draught(cBlackD2, Color::EBlack));
  bWhiteC5E3_G1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteC5E3_G1.put(Draught(cWhiteJumpG1, Color::EWhite, true));
  bWhiteC5E3_G1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteC5E3_G1.put(Draught(cWhiteStartE5, Color::EWhite));
  bWhiteC5E3_G1.put(Draught(cWhiteC7, Color::EWhite));
  CPPUNIT_ASSERT_EQUAL(bWhiteC5E3_G1, b + mWhiteC5E3_G1);
}

void MoveTests::boardPlusComplexJumpNoRequestedDraught()
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

void MoveTests::boardPlusComplexJumpNothingToJumpOver()
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

void MoveTests::boardPlusComplexJumpInWrongDirection()
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

void MoveTests::boardPlusComplexJumpToBusySquare()
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

void MoveTests::boardPlusComplexJumpOverBusySquare()
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

void MoveTests::boardPlusComplexJumpMoreJumpExist()
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

void MoveTests::boardPlusComplexJumpNotTerminatedAfterGetKing()
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

void MoveTests::boardPlusComplexJumpOverSameColor()
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
