#include "MoveTests.h"
#include "Move.h"
#include "Board.h"
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
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleMoveByKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleMoveGetKing()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleMoveNoRequestedDraught()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleMoveInWrongDirection()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleMoveToBusySquare()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
}

void MoveTests::boardPlusSimpleMoveJumpExist()
{
  CPPUNIT_FAIL("NOT IMPLEMENTED");
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
