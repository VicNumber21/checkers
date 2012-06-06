#include "Move.h"
#include "RulesOfGame.h"
#include "ActionAtBoard.h"
#include "PositionAnalyser.h"

using namespace Checkers::Engine;


Move::Move()
  : m_error(new ErrorUndefinedUsage)
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

Move::Move(const Engine::Move &aMove)
  : m_from(aMove.m_from)
  , m_to(aMove.m_to)
  , m_error(aMove.m_error)
{
}

int Move::score() const
{
  return from().count() - to().count();
}

Move::Type Move::type() const
{
  return score() > 0? EJump: ESimple;
}

Move & Move::operator=(const Engine::Move &aMove)
{
  m_from = aMove.m_from;
  m_to = aMove.m_to;
  m_error = aMove.m_error;
  return *this;
}

bool Move::operator==(const Engine::Move &aMove) const
{
  return isValid() && aMove.isValid() && (m_from == aMove.m_from) && (m_to == aMove.m_to);
}

bool Move::operator!=(const Engine::Move &aMove) const
{
  return !(*this == aMove);
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
