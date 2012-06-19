#include "Move.h"
#include "RulesOfGame.h"
#include "PositionAnalyser.h"

using namespace Checkers::Engine;


const int Move::KCoordSequenceIdAny = -1;

Move::Move()
  : m_error(new ErrorUndefinedUsage)
{
}

Move::Move(const Engine::Board &aFrom, const Engine::Board &aTo, int aCoordSequenceId)
  : m_from(aFrom)
  , m_to(aTo)
  , m_coord_sequence_id(aCoordSequenceId)
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
  , m_coord_sequence_id(aMove.m_coord_sequence_id)
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

void Move::setCoordSequenceId(int aId)
{
  m_coord_sequence_id = aId;
}

int Move::coordSequenceId() const
{
  return m_coord_sequence_id;
}

bool Move::anyCoordSequence() const
{
  return (m_coord_sequence_id == KCoordSequenceIdAny);
}

Move & Move::operator=(const Engine::Move &aMove)
{
  m_from = aMove.m_from;
  m_to = aMove.m_to;
  m_error = aMove.m_error;
  m_coord_sequence_id = aMove.m_coord_sequence_id;
  return *this;
}

bool Move::operator==(const Engine::Move &aMove) const
{
  return isValid() && aMove.isValid() && (m_from == aMove.m_from) && (m_to == aMove.m_to) && (m_coord_sequence_id == aMove.m_coord_sequence_id);
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
