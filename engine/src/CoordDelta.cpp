#include "CoordDelta.h"

#include <stdlib.h>
#include <algorithm>

using namespace Checkers::Engine;


CoordDelta::CoordDelta(Direction aDirection, int aDistance)
  : m_dx(aDirection & EWestFlag? -aDistance: aDirection & EEastFlag? aDistance: 0)
  , m_dy(aDirection & ESouthFlag? -aDistance: aDirection & ENorthFlag? aDistance: 0)
{
}

CoordDelta::CoordDelta(int aDeltaX, int aDeltaY)
  : m_dx(aDeltaX)
  , m_dy(aDeltaY)
{
}

CoordDelta::CoordDelta(const CoordDelta &aDelta)
  : m_dx(aDelta.m_dx)
  , m_dy(aDelta.m_dy)
{
}

int CoordDelta::x() const
{
  return m_dx;
}

int CoordDelta::y() const
{
  return m_dy;
}

bool CoordDelta::isNull() const
{
  return (m_dx == 0) && (m_dy == 0);
}

bool CoordDelta::isHorizontal() const
{
  return (m_dy == 0);
}

bool CoordDelta::isVertical() const
{
  return (m_dx == 0);
}

bool CoordDelta::isDiagonal() const
{
  return (abs(m_dx) == abs(m_dy));
}

bool CoordDelta::isSymmetric() const
{
  return isHorizontal() || isVertical() || isDiagonal();
}

CoordDelta::Direction CoordDelta::direction() const
{
  DirectionFlag verticalFlag = static_cast<DirectionFlag>(0);
  DirectionFlag horizontalFlag = static_cast<DirectionFlag>(0);

  if(m_dx > 0)
  {
    horizontalFlag = EEastFlag;
  }
  else if(m_dx < 0)
  {
    horizontalFlag = EWestFlag;
  }

  if(m_dy > 0)
  {
    verticalFlag = ENorthFlag;
  }
  else if(m_dy < 0)
  {
    verticalFlag = ESouthFlag;
  }

  int mask = ~((~0) << 4);

  return static_cast<Direction>(mask & (horizontalFlag | verticalFlag));
}

bool CoordDelta::isNorth() const
{
  return direction() & ENorthFlag;
}

bool CoordDelta::isSouth() const
{
  return direction() & ESouthFlag;
}

bool CoordDelta::isWest() const
{
  return direction() & EWestFlag;
}

bool CoordDelta::isEast() const
{
  return direction() & EEastFlag;
}

int CoordDelta::distance() const
{
  return isSymmetric()? std::max(abs(m_dx), abs(m_dy)): -1;
}

CoordDelta & CoordDelta::operator=(const CoordDelta &aDelta)
{
  m_dx = aDelta.m_dx;
  m_dy = aDelta.m_dy;
  return *this;
}

bool CoordDelta::operator==(const CoordDelta &aDelta) const
{
  return (m_dx == aDelta.m_dx) && (m_dy == aDelta.m_dy);
}

Coord Checkers::Engine::operator+(const Coord &aCoord, const CoordDelta &aDelta)
{
  return Coord(aCoord.x() + aDelta.x(), aCoord.y() + aDelta.y());
}

Coord Checkers::Engine::operator-(const Coord &aCoord, const CoordDelta &aDelta)
{
  return Coord(aCoord.x() - aDelta.x(), aCoord.y() - aDelta.y());
}

CoordDelta Checkers::Engine::operator-(const Coord &aFirst, const Coord &aSecond)
{
  return CoordDelta(aFirst.x() - aSecond.x(), aFirst.y() - aSecond.y());
}
