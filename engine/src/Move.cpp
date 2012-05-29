#include "Move.h"
#include "RulesOfGame.h"
#include "ActionAtBoard.h"

using namespace Checkers::Engine;


Move::Move()
  : m_type(EUndefined)
{
}

Move::Move(const Engine::Coord &aStart, const Engine::Coord &aNext, Type aType)
  : m_type(aType)
{
  m_coords.append(aStart);
  m_coords.append(aNext);
  m_coords.depricatedValidation(aType == EJump);
}

Move::Move(const Engine::Move &aMove)
  : m_coords(aMove.m_coords)
  , m_type(aMove.m_type)
{
}

void Move::append(const Engine::Coord &aNext)
{
  throwIfUndefined();

  if(m_type != EJump)
    throw ErrorUnexpectedAppend();

  m_coords.append(aNext);
}

int Move::score() const
{
  throwIfUndefined();

  int ret = 0;

  if(type() == EJump)
  {
    ret = m_coords.count() - 1;
  }

  return ret;
}

Move::Type Move::type() const
{
  return m_type;
}

Move & Move::operator=(const Engine::Move &aMove)
{
  m_coords = aMove.m_coords;
  m_type = aMove.m_type;
  return *this;
}

bool Move::operator==(const Engine::Move &aMove) const
{
  return  (m_type == aMove.m_type) && (m_coords == aMove.m_coords);
}

bool Move::operator!=(const Engine::Move &aMove) const
{
  return !(*this == aMove);
}

const CoordSequence & Move::coords() const
{
  throwIfUndefined();
  return m_coords;
}

void Move::throwIfUndefined() const
{
  if(m_type == EUndefined)
    throw ErrorUndefinedUsage();
}

Board Checkers::Engine::operator+(const Board &aCurrent, const Move &aMove)
{
  ActionAtBoard::Ptr action = RulesOfGame::MoveValidator::transformIntoActions(aCurrent, aMove.coords());

  if(!action)
    throw Move::ErrorUnknown();

  Board ret(aCurrent);
  action->perform(ret);

  return ret;
}

/* TODO Remove if not needed
Board Checkers::Engine::operator-(const Board &aNext, const Move &aMove)
{
  (void)aNext;
  (void)aMove;

  return Board();
}
*/

Move Checkers::Engine::operator-(const Board &aNext, const Board &aCurrent)
{
  (void)aCurrent;
  (void)aNext;

  return Move();
}
