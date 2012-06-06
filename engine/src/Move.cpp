#include "Move.h"
#include "RulesOfGame.h"
#include "ActionAtBoard.h"
#include "PositionAnalyser.h"

using namespace Checkers::Engine;


Move::Move()
  : m_error(new ErrorUndefinedUsage)
  , m_type(EUndefined)
{
}

Move::Move(const Engine::Board &aFrom, const Engine::Board &aTo)
  : m_from(aFrom)
  , m_to(aTo)
{
}

Move::Move(const Engine::Error::Ptr aError)
  : m_error(aError)
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
  : m_from(aMove.m_from)
  , m_to(aMove.m_to)
  , m_error(aMove.m_error)
  , m_coords(aMove.m_coords)
  , m_type(aMove.m_type)
{
}

void Move::append(const Engine::Coord &aNext)
{
  throwIfInvalid();

  if(m_type != EJump)
    throw ErrorUnexpectedAppend();

  m_coords.append(aNext);
}

int Move::score() const
{
  throwIfInvalid();

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
  m_from = aMove.m_from;
  m_to = aMove.m_to;
  m_error = aMove.m_error;
  m_coords = aMove.m_coords;
  m_type = aMove.m_type;
  return *this;
}

bool Move::operator==(const Engine::Move &aMove) const
{
  return isValid() && aMove.isValid() && (m_from == aMove.m_from) && (m_to == aMove.m_to)
         && (m_type == aMove.m_type) && (m_coords == aMove.m_coords);
}

bool Move::operator!=(const Engine::Move &aMove) const
{
  return !(*this == aMove);
}

const CoordSequence & Move::coords() const
{
  throwIfInvalid();
  return m_coords;
}

const Board & Move::from() const
{
  throwIfInvalid();
  return m_from;
}

const Board & Move::to() const
{
  throwIfInvalid();
  return m_to;
}

bool Move::isValid() const
{
  return m_error == 0;
}

Checkers::Engine::Error::Ptr Move::error() const
{
  return m_error;
}

void Move::throwIfInvalid() const
{
  if(!isValid())
    m_error->raise();
}
