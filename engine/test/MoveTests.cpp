#include "MoveTests.h"
#include "Move.h"
#include "Board.h"
#include "Draught.h"
#include "Color.h"
#include "Coord.h"
#include "PrettyPrint.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( MoveTests );


MoveTests::MoveTests()
{
  m_error_move_1 = Move(Error::Ptr(new Move::ErrorGetKingButMoveFurther));
  m_error_move_2 = Move(Error::Ptr(new Move::ErrorNoRequestedDraught));

  Coord cA3('a', '3');
  Coord cA5('a', '5');
  Coord cB4('b', '4');
  Coord cC5('c', '5');
  Coord cD4('d', '4');
  Coord cD6('d', '6');
  Coord cE3('e', '3');
  Coord cE7('e', '7');
  Coord cF6('f', '6');
  Coord cG5('g', '5');

  Board bSimpleMoveFrom;
  bSimpleMoveFrom.put(Draught(cB4, Color::EBlack));
  Board bSimpleMoveTo;
  bSimpleMoveTo.put(Draught(cC5, Color::EBlack));
  m_simple_move_1_any_id = Move(bSimpleMoveFrom, bSimpleMoveTo);
  m_simple_move_1_id_2 = Move(bSimpleMoveFrom, bSimpleMoveTo, 2);

  Board bAnotherSimpleMoveTo;
  bAnotherSimpleMoveTo.put(Draught(cA5, Color::EBlack));
  m_simple_move_2 = Move(bSimpleMoveFrom, bAnotherSimpleMoveTo);

  Board bSimpleJumpFrom;
  bSimpleJumpFrom.put(Draught(cA3, Color::EBlack));
  bSimpleJumpFrom.put(Draught(cB4, Color::EWhite));
  Board bSimpleJumpTo;
  bSimpleJumpTo.put(Draught(cC5, Color::EBlack));
  m_simple_jump_1 = Move(bSimpleJumpFrom, bSimpleJumpTo);

  Board bAnotherSimpleJumpFrom;
  bAnotherSimpleJumpFrom.put(Draught(cE3, Color::EBlack));
  bAnotherSimpleJumpFrom.put(Draught(cD4, Color::EWhite));
  m_simple_jump_2 = Move(bAnotherSimpleJumpFrom, bSimpleJumpTo);

  Board bComplexJumpFrom;
  bComplexJumpFrom.put(Draught(cA3, Color::EBlack));
  bComplexJumpFrom.put(Draught(cB4, Color::EWhite));
  bComplexJumpFrom.put(Draught(cD6, Color::EWhite));
  Board bComplexJumpTo;
  bComplexJumpTo.put(Draught(cE7, Color::EBlack));
  m_complex_jump_1 = Move(bComplexJumpFrom, bComplexJumpTo);

  Board bAnotherComplexJumpFrom;
  bAnotherComplexJumpFrom.put(Draught(cE3, Color::EBlack, true));
  bAnotherComplexJumpFrom.put(Draught(cD4, Color::EWhite));
  bAnotherComplexJumpFrom.put(Draught(cD6, Color::EWhite));
  bAnotherComplexJumpFrom.put(Draught(cF6, Color::EWhite));

  Board bAnotherComplexJumpTo;
  bAnotherComplexJumpTo.put(Draught(cG5, Color::EBlack, true));
  m_complex_jump_2 = Move(bAnotherComplexJumpFrom, bAnotherComplexJumpTo);
}

void MoveTests::setUp()
{
}

void MoveTests::tearDown()
{
}

void MoveTests::undefinedUsage()
{
  CPPUNIT_ASSERT_THROW(m_empty_move.from(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m_empty_move.to(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m_empty_move.type(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m_empty_move.score(), Move::ErrorUndefinedUsage);
}

void MoveTests::wrongConstruction()
{
  Board b;
  Move mEmptyFrom(b, b);
  CPPUNIT_ASSERT_THROW(mEmptyFrom.score(), Move::ErrorEmptyFromBoard);

  b.put(Draught(Coord('a', '1'), Color::EBlack));
  Move mSameFromAndTo(b, b);
  CPPUNIT_ASSERT_THROW(mSameFromAndTo.score(), Move::ErrorSameFromAndTo);
}

void MoveTests::equalError()
{
  Move m;
  //Wrong move are different ever
  CPPUNIT_ASSERT(!(m == m_empty_move));
  CPPUNIT_ASSERT(!(m_empty_move == m_empty_move));
  CPPUNIT_ASSERT(!(m_empty_move == m_error_move_1));
  CPPUNIT_ASSERT(!(m_empty_move == m_simple_move_2));
  CPPUNIT_ASSERT(!(m_empty_move == m_simple_jump_2));
  CPPUNIT_ASSERT(!(m_empty_move == m_complex_jump_2));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_error_move_2));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_simple_move_2));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_simple_jump_2));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_complex_jump_2));
}

void MoveTests::equalSimpleMove()
{
  Move m;
  m = m_simple_move_1_any_id;
  CPPUNIT_ASSERT(m == m_simple_move_1_any_id);

  Move mCopy(m_simple_move_2);
  CPPUNIT_ASSERT(mCopy == m_simple_move_2);

  CPPUNIT_ASSERT(m_simple_move_1_any_id == m_simple_move_1_any_id);
  CPPUNIT_ASSERT(m_simple_move_2 == m_simple_move_2);
  CPPUNIT_ASSERT(!(m_simple_move_1_any_id == m_simple_move_2));
  CPPUNIT_ASSERT(!(m_simple_move_1_any_id == m_simple_jump_2));
  CPPUNIT_ASSERT(!(m_simple_move_1_any_id == m_complex_jump_2));
}

void MoveTests::equalSimpleJump()
{
  Move m;
  m = m_simple_jump_1;
  CPPUNIT_ASSERT(m == m_simple_jump_1);

  Move mCopy(m_simple_jump_2);
  CPPUNIT_ASSERT(mCopy == m_simple_jump_2);

  CPPUNIT_ASSERT(m_simple_jump_1 == m_simple_jump_1);
  CPPUNIT_ASSERT(m_simple_jump_2 == m_simple_jump_2);
  CPPUNIT_ASSERT(!(m_simple_jump_1 == m_simple_move_2));
  CPPUNIT_ASSERT(!(m_simple_jump_1 == m_simple_jump_2));
  CPPUNIT_ASSERT(!(m_simple_jump_1 == m_complex_jump_2));
}

void MoveTests::equalComplexJump()
{
  Move m;
  m = m_complex_jump_1;
  CPPUNIT_ASSERT(m == m_complex_jump_1);

  Move mCopy(m_complex_jump_2);
  CPPUNIT_ASSERT(mCopy == m_complex_jump_2);

  CPPUNIT_ASSERT(m_complex_jump_1 == m_complex_jump_1);
  CPPUNIT_ASSERT(m_complex_jump_2 == m_complex_jump_2);
  CPPUNIT_ASSERT(!(m_complex_jump_1 == m_simple_move_2));
  CPPUNIT_ASSERT(!(m_complex_jump_1 == m_simple_jump_2));
  CPPUNIT_ASSERT(!(m_complex_jump_1 == m_complex_jump_2));
}

void MoveTests::notEqualError()
{
  Move m;
  //Wrong move are different ever
  CPPUNIT_ASSERT(m != m_empty_move);
  CPPUNIT_ASSERT(m_empty_move != m_empty_move);
  CPPUNIT_ASSERT(m_empty_move != m_error_move_1);
  CPPUNIT_ASSERT(m_empty_move != m_simple_move_1_any_id);
  CPPUNIT_ASSERT(m_empty_move != m_simple_jump_1);
  CPPUNIT_ASSERT(m_empty_move != m_complex_jump_1);
  CPPUNIT_ASSERT(m_error_move_1 != m_error_move_2);
  CPPUNIT_ASSERT(m_error_move_1 != m_simple_move_1_any_id);
  CPPUNIT_ASSERT(m_error_move_1 != m_simple_jump_1);
  CPPUNIT_ASSERT(m_error_move_1 != m_complex_jump_1);
}

void MoveTests::notEqualSimpleMove()
{
  Move m;
  m = m_simple_move_1_any_id;
  CPPUNIT_ASSERT(!(m != m_simple_move_1_any_id));

  Move mCopy(m_simple_move_2);
  CPPUNIT_ASSERT(!(mCopy != m_simple_move_2));

  CPPUNIT_ASSERT(!(m_simple_move_1_any_id != m_simple_move_1_any_id));
  CPPUNIT_ASSERT(!(m_simple_move_2 != m_simple_move_2));
  CPPUNIT_ASSERT(m_simple_move_1_any_id != m_simple_move_2);
  CPPUNIT_ASSERT(m_simple_move_1_any_id != m_simple_jump_2);
  CPPUNIT_ASSERT(m_simple_move_1_any_id != m_complex_jump_2);
}

void MoveTests::notEqualSimpleJump()
{
  Move m;
  m = m_simple_jump_1;
  CPPUNIT_ASSERT(!(m != m_simple_jump_1));

  Move mCopy(m_simple_jump_2);
  CPPUNIT_ASSERT(!(mCopy != m_simple_jump_2));

  CPPUNIT_ASSERT(!(m_simple_jump_1 != m_simple_jump_1));
  CPPUNIT_ASSERT(!(m_simple_jump_2 != m_simple_jump_2));
  CPPUNIT_ASSERT(m_simple_jump_1 != m_simple_move_2);
  CPPUNIT_ASSERT(m_simple_jump_1 != m_simple_jump_2);
  CPPUNIT_ASSERT(m_simple_jump_1 != m_complex_jump_2);
}

void MoveTests::notEqualComplexJump()
{
  Move m;
  m = m_complex_jump_1;
  CPPUNIT_ASSERT(!(m != m_complex_jump_1));

  Move mCopy(m_complex_jump_2);
  CPPUNIT_ASSERT(!(mCopy != m_complex_jump_2));

  CPPUNIT_ASSERT(!(m_complex_jump_1 != m_complex_jump_1));
  CPPUNIT_ASSERT(!(m_complex_jump_2 != m_complex_jump_2));
  CPPUNIT_ASSERT(m_complex_jump_1 != m_simple_move_2);
  CPPUNIT_ASSERT(m_complex_jump_1 != m_simple_jump_2);
  CPPUNIT_ASSERT(m_complex_jump_1 != m_complex_jump_2);
}

void MoveTests::type()
{
  CPPUNIT_ASSERT_EQUAL(Move::ESimple, m_simple_move_1_any_id.type());
  CPPUNIT_ASSERT_EQUAL(Move::ESimple, m_simple_move_2.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_simple_jump_1.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_simple_jump_2.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_complex_jump_1.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_complex_jump_2.type());
}

void MoveTests::isValid()
{
  CPPUNIT_ASSERT(!m_empty_move.isValid());
  CPPUNIT_ASSERT(!m_error_move_1.isValid());
  CPPUNIT_ASSERT(!m_error_move_2.isValid());
  CPPUNIT_ASSERT(m_simple_move_1_any_id.isValid());
  CPPUNIT_ASSERT(m_simple_move_2.isValid());
  CPPUNIT_ASSERT(m_simple_jump_1.isValid());
  CPPUNIT_ASSERT(m_simple_jump_2.isValid());
  CPPUNIT_ASSERT(m_complex_jump_1.isValid());
  CPPUNIT_ASSERT(m_complex_jump_2.isValid());
}

void MoveTests::error()
{
  CPPUNIT_ASSERT(m_empty_move.error());
  CPPUNIT_ASSERT(m_error_move_1.error());
  CPPUNIT_ASSERT(m_error_move_2.error());
  CPPUNIT_ASSERT(!m_simple_move_1_any_id.error());
  CPPUNIT_ASSERT(!m_simple_move_2.error());
  CPPUNIT_ASSERT(!m_simple_jump_1.error());
  CPPUNIT_ASSERT(!m_simple_jump_2.error());
  CPPUNIT_ASSERT(!m_complex_jump_1.error());
  CPPUNIT_ASSERT(!m_complex_jump_2.error());
}

void MoveTests::simpleMoveScore()
{
  CPPUNIT_ASSERT_EQUAL(0, m_simple_move_1_any_id.score());
  CPPUNIT_ASSERT_EQUAL(0, m_simple_move_2.score());
}

void MoveTests::simpleJumpScore()
{
  CPPUNIT_ASSERT_EQUAL(1, m_simple_jump_1.score());
  CPPUNIT_ASSERT_EQUAL(1, m_simple_jump_2.score());
}

void MoveTests::complexJumpScore()
{
  CPPUNIT_ASSERT_EQUAL(2, m_complex_jump_1.score());
  CPPUNIT_ASSERT_EQUAL(3, m_complex_jump_2.score());
}

void MoveTests::coordSequenceId()
{
  CPPUNIT_ASSERT_EQUAL(Move::KCoordSequenceIdAny, m_simple_move_1_any_id.coordSequenceId());
  CPPUNIT_ASSERT_EQUAL(2, m_simple_move_1_id_2.coordSequenceId());
  CPPUNIT_ASSERT(m_simple_move_1_any_id.anyCoordSequence());
  CPPUNIT_ASSERT(!m_simple_move_1_id_2.anyCoordSequence());

  m_simple_move_1_id_2.setCoordSequenceId(5);
  CPPUNIT_ASSERT_EQUAL(5, m_simple_move_1_id_2.coordSequenceId());
  CPPUNIT_ASSERT(!m_simple_move_1_id_2.anyCoordSequence());

  m_simple_move_1_id_2.setCoordSequenceId(Move::KCoordSequenceIdAny);
  CPPUNIT_ASSERT_EQUAL(Move::KCoordSequenceIdAny, m_simple_move_1_id_2.coordSequenceId());
  CPPUNIT_ASSERT(m_simple_move_1_id_2.anyCoordSequence());

  m_simple_move_1_id_2.setCoordSequenceId(2);
  CPPUNIT_ASSERT_EQUAL(2, m_simple_move_1_id_2.coordSequenceId());
  CPPUNIT_ASSERT(!m_simple_move_1_id_2.anyCoordSequence());
}
