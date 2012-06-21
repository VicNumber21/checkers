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

  Board bBlackSimpleMoveFrom;
  bBlackSimpleMoveFrom.put(Draught(cB4, Color::EBlack));
  Board bBlackSimpleMoveTo;
  bBlackSimpleMoveTo.put(Draught(cC5, Color::EBlack));
  m_simple_move_black_any_id = Move(bBlackSimpleMoveFrom, bBlackSimpleMoveTo);
  m_simple_move_black_id_2 = Move(bBlackSimpleMoveFrom, bBlackSimpleMoveTo, 2);

  Board bWhiteSimpleMoveFrom;
  bWhiteSimpleMoveFrom.put(Draught(cD6, Color::EWhite));
  Board bWhiteSimpleMoveTo;
  bWhiteSimpleMoveTo.put(Draught(cA5, Color::EWhite));
  m_simple_move_white = Move(bWhiteSimpleMoveFrom, bWhiteSimpleMoveTo);

  Board bBlackSimpleJumpFrom;
  bBlackSimpleJumpFrom.put(Draught(cA3, Color::EBlack));
  bBlackSimpleJumpFrom.put(Draught(cB4, Color::EWhite));
  Board bBlackSimpleJumpTo;
  bBlackSimpleJumpTo.put(Draught(cC5, Color::EBlack));
  m_simple_jump_black = Move(bBlackSimpleJumpFrom, bBlackSimpleJumpTo);

  Board bWhiteSimpleJumpFrom;
  bWhiteSimpleJumpFrom.put(Draught(cC5, Color::EWhite));
  bWhiteSimpleJumpFrom.put(Draught(cD4, Color::EBlack));
  Board bWhiteSimpleJumpTo;
  bWhiteSimpleJumpTo.put(Draught(cE3, Color::EWhite));
  m_simple_jump_white = Move(bWhiteSimpleJumpFrom, bWhiteSimpleJumpTo);

  Board bBlackComplexJumpFrom;
  bBlackComplexJumpFrom.put(Draught(cA3, Color::EBlack));
  bBlackComplexJumpFrom.put(Draught(cB4, Color::EWhite));
  bBlackComplexJumpFrom.put(Draught(cD6, Color::EWhite));
  Board bBlackComplexJumpTo;
  bBlackComplexJumpTo.put(Draught(cE7, Color::EBlack));
  m_complex_jump_black = Move(bBlackComplexJumpFrom, bBlackComplexJumpTo);

  Board bWhiteComplexJumpFrom;
  bWhiteComplexJumpFrom.put(Draught(cE3, Color::EWhite, true));
  bWhiteComplexJumpFrom.put(Draught(cD4, Color::EBlack));
  bWhiteComplexJumpFrom.put(Draught(cD6, Color::EBlack));
  bWhiteComplexJumpFrom.put(Draught(cF6, Color::EBlack));

  Board bWhiteComplexJumpTo;
  bWhiteComplexJumpTo.put(Draught(cG5, Color::EWhite, true));
  m_complex_jump_white = Move(bWhiteComplexJumpFrom, bWhiteComplexJumpTo);
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
  CPPUNIT_ASSERT_THROW(m_empty_move.color(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m_empty_move.anyCoordSequence(), Move::ErrorUndefinedUsage);
  CPPUNIT_ASSERT_THROW(m_empty_move.coordSequenceId(), Move::ErrorUndefinedUsage);
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
  CPPUNIT_ASSERT(!(m_empty_move == m_simple_move_white));
  CPPUNIT_ASSERT(!(m_empty_move == m_simple_jump_white));
  CPPUNIT_ASSERT(!(m_empty_move == m_complex_jump_white));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_error_move_2));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_simple_move_white));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_simple_jump_white));
  CPPUNIT_ASSERT(!(m_error_move_1 == m_complex_jump_white));
}

void MoveTests::equalSimpleMove()
{
  Move m;
  m = m_simple_move_black_any_id;
  CPPUNIT_ASSERT(m == m_simple_move_black_any_id);

  Move mCopy(m_simple_move_white);
  CPPUNIT_ASSERT(mCopy == m_simple_move_white);

  CPPUNIT_ASSERT(m_simple_move_black_any_id == m_simple_move_black_any_id);
  CPPUNIT_ASSERT(m_simple_move_white == m_simple_move_white);
  CPPUNIT_ASSERT(!(m_simple_move_black_any_id == m_simple_move_white));
  CPPUNIT_ASSERT(!(m_simple_move_black_any_id == m_simple_jump_white));
  CPPUNIT_ASSERT(!(m_simple_move_black_any_id == m_complex_jump_white));
}

void MoveTests::equalSimpleJump()
{
  Move m;
  m = m_simple_jump_black;
  CPPUNIT_ASSERT(m == m_simple_jump_black);

  Move mCopy(m_simple_jump_white);
  CPPUNIT_ASSERT(mCopy == m_simple_jump_white);

  CPPUNIT_ASSERT(m_simple_jump_black == m_simple_jump_black);
  CPPUNIT_ASSERT(m_simple_jump_white == m_simple_jump_white);
  CPPUNIT_ASSERT(!(m_simple_jump_black == m_simple_move_white));
  CPPUNIT_ASSERT(!(m_simple_jump_black == m_simple_jump_white));
  CPPUNIT_ASSERT(!(m_simple_jump_black == m_complex_jump_white));
}

void MoveTests::equalComplexJump()
{
  Move m;
  m = m_complex_jump_black;
  CPPUNIT_ASSERT(m == m_complex_jump_black);

  Move mCopy(m_complex_jump_white);
  CPPUNIT_ASSERT(mCopy == m_complex_jump_white);

  CPPUNIT_ASSERT(m_complex_jump_black == m_complex_jump_black);
  CPPUNIT_ASSERT(m_complex_jump_white == m_complex_jump_white);
  CPPUNIT_ASSERT(!(m_complex_jump_black == m_simple_move_white));
  CPPUNIT_ASSERT(!(m_complex_jump_black == m_simple_jump_white));
  CPPUNIT_ASSERT(!(m_complex_jump_black == m_complex_jump_white));
}

void MoveTests::notEqualError()
{
  Move m;
  //Wrong move are different ever
  CPPUNIT_ASSERT(m != m_empty_move);
  CPPUNIT_ASSERT(m_empty_move != m_empty_move);
  CPPUNIT_ASSERT(m_empty_move != m_error_move_1);
  CPPUNIT_ASSERT(m_empty_move != m_simple_move_black_any_id);
  CPPUNIT_ASSERT(m_empty_move != m_simple_jump_black);
  CPPUNIT_ASSERT(m_empty_move != m_complex_jump_black);
  CPPUNIT_ASSERT(m_error_move_1 != m_error_move_2);
  CPPUNIT_ASSERT(m_error_move_1 != m_simple_move_black_any_id);
  CPPUNIT_ASSERT(m_error_move_1 != m_simple_jump_black);
  CPPUNIT_ASSERT(m_error_move_1 != m_complex_jump_black);
}

void MoveTests::notEqualSimpleMove()
{
  Move m;
  m = m_simple_move_black_any_id;
  CPPUNIT_ASSERT(!(m != m_simple_move_black_any_id));

  Move mCopy(m_simple_move_white);
  CPPUNIT_ASSERT(!(mCopy != m_simple_move_white));

  CPPUNIT_ASSERT(!(m_simple_move_black_any_id != m_simple_move_black_any_id));
  CPPUNIT_ASSERT(!(m_simple_move_white != m_simple_move_white));
  CPPUNIT_ASSERT(m_simple_move_black_any_id != m_simple_move_white);
  CPPUNIT_ASSERT(m_simple_move_black_any_id != m_simple_jump_white);
  CPPUNIT_ASSERT(m_simple_move_black_any_id != m_complex_jump_white);
}

void MoveTests::notEqualSimpleJump()
{
  Move m;
  m = m_simple_jump_black;
  CPPUNIT_ASSERT(!(m != m_simple_jump_black));

  Move mCopy(m_simple_jump_white);
  CPPUNIT_ASSERT(!(mCopy != m_simple_jump_white));

  CPPUNIT_ASSERT(!(m_simple_jump_black != m_simple_jump_black));
  CPPUNIT_ASSERT(!(m_simple_jump_white != m_simple_jump_white));
  CPPUNIT_ASSERT(m_simple_jump_black != m_simple_move_white);
  CPPUNIT_ASSERT(m_simple_jump_black != m_simple_jump_white);
  CPPUNIT_ASSERT(m_simple_jump_black != m_complex_jump_white);
}

void MoveTests::notEqualComplexJump()
{
  Move m;
  m = m_complex_jump_black;
  CPPUNIT_ASSERT(!(m != m_complex_jump_black));

  Move mCopy(m_complex_jump_white);
  CPPUNIT_ASSERT(!(mCopy != m_complex_jump_white));

  CPPUNIT_ASSERT(!(m_complex_jump_black != m_complex_jump_black));
  CPPUNIT_ASSERT(!(m_complex_jump_white != m_complex_jump_white));
  CPPUNIT_ASSERT(m_complex_jump_black != m_simple_move_white);
  CPPUNIT_ASSERT(m_complex_jump_black != m_simple_jump_white);
  CPPUNIT_ASSERT(m_complex_jump_black != m_complex_jump_white);
}

void MoveTests::type()
{
  CPPUNIT_ASSERT_EQUAL(Move::ESimple, m_simple_move_black_any_id.type());
  CPPUNIT_ASSERT_EQUAL(Move::ESimple, m_simple_move_white.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_simple_jump_black.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_simple_jump_white.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_complex_jump_black.type());
  CPPUNIT_ASSERT_EQUAL(Move::EJump, m_complex_jump_white.type());
}

void MoveTests::isValid()
{
  CPPUNIT_ASSERT(!m_empty_move.isValid());
  CPPUNIT_ASSERT(!m_error_move_1.isValid());
  CPPUNIT_ASSERT(!m_error_move_2.isValid());
  CPPUNIT_ASSERT(m_simple_move_black_any_id.isValid());
  CPPUNIT_ASSERT(m_simple_move_white.isValid());
  CPPUNIT_ASSERT(m_simple_jump_black.isValid());
  CPPUNIT_ASSERT(m_simple_jump_white.isValid());
  CPPUNIT_ASSERT(m_complex_jump_black.isValid());
  CPPUNIT_ASSERT(m_complex_jump_white.isValid());
}

void MoveTests::error()
{
  CPPUNIT_ASSERT(m_empty_move.error());
  CPPUNIT_ASSERT(m_error_move_1.error());
  CPPUNIT_ASSERT(m_error_move_2.error());
  CPPUNIT_ASSERT(!m_simple_move_black_any_id.error());
  CPPUNIT_ASSERT(!m_simple_move_white.error());
  CPPUNIT_ASSERT(!m_simple_jump_black.error());
  CPPUNIT_ASSERT(!m_simple_jump_white.error());
  CPPUNIT_ASSERT(!m_complex_jump_black.error());
  CPPUNIT_ASSERT(!m_complex_jump_white.error());
}

void MoveTests::simpleMoveScore()
{
  CPPUNIT_ASSERT_EQUAL(0, m_simple_move_black_any_id.score());
  CPPUNIT_ASSERT_EQUAL(0, m_simple_move_white.score());
}

void MoveTests::simpleJumpScore()
{
  CPPUNIT_ASSERT_EQUAL(1, m_simple_jump_black.score());
  CPPUNIT_ASSERT_EQUAL(1, m_simple_jump_white.score());
}

void MoveTests::complexJumpScore()
{
  CPPUNIT_ASSERT_EQUAL(2, m_complex_jump_black.score());
  CPPUNIT_ASSERT_EQUAL(3, m_complex_jump_white.score());
}

void MoveTests::coordSequenceId()
{
  CPPUNIT_ASSERT_EQUAL(Move::KCoordSequenceIdAny, m_simple_move_black_any_id.coordSequenceId());
  CPPUNIT_ASSERT_EQUAL(2, m_simple_move_black_id_2.coordSequenceId());
  CPPUNIT_ASSERT(m_simple_move_black_any_id.anyCoordSequence());
  CPPUNIT_ASSERT(!m_simple_move_black_id_2.anyCoordSequence());

  m_simple_move_black_id_2.setCoordSequenceId(5);
  CPPUNIT_ASSERT_EQUAL(5, m_simple_move_black_id_2.coordSequenceId());
  CPPUNIT_ASSERT(!m_simple_move_black_id_2.anyCoordSequence());

  m_simple_move_black_id_2.setCoordSequenceId(Move::KCoordSequenceIdAny);
  CPPUNIT_ASSERT_EQUAL(Move::KCoordSequenceIdAny, m_simple_move_black_id_2.coordSequenceId());
  CPPUNIT_ASSERT(m_simple_move_black_id_2.anyCoordSequence());

  m_simple_move_black_id_2.setCoordSequenceId(2);
  CPPUNIT_ASSERT_EQUAL(2, m_simple_move_black_id_2.coordSequenceId());
  CPPUNIT_ASSERT(!m_simple_move_black_id_2.anyCoordSequence());
}

void MoveTests::color()
{
  CPPUNIT_ASSERT(Color::EBlack == m_simple_move_black_any_id.color());
  CPPUNIT_ASSERT(Color::EWhite == m_simple_move_white.color());
  CPPUNIT_ASSERT(Color::EBlack == m_simple_jump_black.color());
  CPPUNIT_ASSERT(Color::EWhite == m_simple_jump_white.color());
  CPPUNIT_ASSERT(Color::EBlack == m_complex_jump_black.color());
  CPPUNIT_ASSERT(Color::EWhite == m_complex_jump_white.color());
}
