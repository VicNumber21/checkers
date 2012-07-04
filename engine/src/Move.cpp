#include "Move.h"
#include "RulesOfGame.h"
#include "Color.h"

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
  if(aFrom.count() == 0)
    m_error.reset(new ErrorEmptyFromBoard);
  else if(aFrom == aTo) //TODO <- check if it is not too expensive during optimization
    m_error.reset(new ErrorSameFromAndTo);
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

Color Move::color() const
{
  Color ret(Color::EBlack);

  if(score() > 0)
  {
    if(from().count(Color::EBlack) != to().count(Color::EBlack))
    {
      ret = Color::EWhite;
    }
  }
  else
  {
    //TODO can be optimized with hash map usage probably
    Board::Iterator toIt = to().begin();
    for(; toIt != to().end(); ++toIt)
    {
      if(from().testSquare(toIt->coord()).isNothing())
        break;
    }

    ret = toIt->color();
  }

  return ret;
}

void Move::setCoordSequenceId(int aId)
{
  m_coord_sequence_id = aId;
}

int Move::coordSequenceId() const
{
  throwIfInvalid();
  return m_coord_sequence_id;
}

bool Move::anyCoordSequence() const
{
  throwIfInvalid();
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
