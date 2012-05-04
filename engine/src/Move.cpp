#include "Move.h"
#include "RulesOfGame.h"

using namespace Checkers::Engine;


Move::ErrorCoordSequence::ErrorCoordSequence(const Move::CoordList &aCoordList)
  : m_coord_list(aCoordList)
{
}

Move::Move()
  : m_type(EUndefined)
{
}

Move::Move(const Engine::Coord &aStart, const Engine::Coord &aNext, Type aType)
  : m_type(aType)
{
  m_coord_list.push_front(aStart);
  m_coord_list.push_back(aNext);
  validateTail();
}

Move::Move(const Engine::Move &aMove)
  : m_coord_list(aMove.m_coord_list)
  , m_type(aMove.m_type)
{
}

void Move::append(const Engine::Coord &aNext)
{
  throwIfUndefined();

  if(m_type != EJump)
    throw ErrorUnexpectedAppend();

  m_coord_list.push_back(aNext);
  validateTail();
}

int Move::score() const
{
  throwIfUndefined();

  int ret = 0;

  if(type() == EJump)
  {
    ret = m_coord_list.size() - 1;
  }

  return ret;
}

Move::Type Move::type() const
{
  return m_type;
}

Move & Move::operator=(const Engine::Move &aMove)
{
  m_coord_list = aMove.m_coord_list;
  m_type = aMove.m_type;
  return *this;
}

bool Move::operator==(const Engine::Move &aMove) const
{
  return  (m_type == aMove.m_type) && (m_coord_list == aMove.m_coord_list);
}

bool Move::operator!=(const Engine::Move &aMove) const
{
  return !(*this == aMove);
}

Move::Iterator Move::begin() const
{
  throwIfUndefined();
  return m_coord_list.begin();
}

Move::Iterator Move::end() const
{
  throwIfUndefined();
  return m_coord_list.end();
}

void Move::validateTail() const
{
  Iterator beforeLast = --end();
  Iterator last = beforeLast--;

  if(!RulesOfGame::MoveValidator::isValidCoordSequence(*beforeLast, *last, m_type == EJump)
     || isJumpBack(last, --beforeLast))
  {
    throw ErrorCoordSequence(m_coord_list);
  }
}

void Move::throwIfUndefined() const
{
  if(m_type == EUndefined)
    throw ErrorUndefinedUsage();
}

bool Move::isJumpBack(Iterator aLast, Iterator aThirdFromTail) const
{
  return m_coord_list.size() > 2 && (*aLast == *aThirdFromTail);
}

Board Checkers::Engine::operator+(const Board &aCurrent, const Move &aMove)
{
  (void)aCurrent;
  (void)aMove;

  return Board();
}

Board Checkers::Engine::operator-(const Board &aNext, const Move &aMove)
{
  (void)aNext;
  (void)aMove;

  return Board();
}

Move Checkers::Engine::operator-(const Board &aNext, const Board &aCurrent)
{
  (void)aCurrent;
  (void)aNext;

  return Move();
}
