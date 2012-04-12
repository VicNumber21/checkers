#include "Draught.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;


Draught::Draught(const Engine::Draught &aDraught)
{
  m_value = aDraught.m_value;
}

Draught::Draught(const Engine::Coord &aCoord, const Engine::Color &aColor, bool aIsKing)
{
  coordRef().assign(aCoord);
  colorRef().assign(aColor);
  kingFlagRef().set(aIsKing);
}

Coord Draught::coord() const
{
  return coordConstRef();
}

Color Draught::color() const
{
  return colorConstRef();
}

void Draught::moveTo(const Engine::Coord &aCoord)
{
  coordRef().assign(aCoord);
}

bool Draught::isKing() const
{
  return kingFlagConstRef()();
}

void Draught::makeKing()
{
  kingFlagRef().set(true);
}

bool Draught::operator==(const Engine::Draught &aDraught) const
{
  return coord() == aDraught.coord() && color() == aDraught.color() && isKing() == aDraught.isKing();
}

bool Draught::operator!=(const Engine::Draught &aDraught) const
{
  return !(*this == aDraught);
}

bool Draught::operator<(const Engine::Draught &aDraught) const
{
  return coord() < aDraught.coord();
}

bool Draught::operator>(const Engine::Draught &aDraught) const
{
  return coord() > aDraught.coord();
}

CoordBase & Draught::coordRef()
{
  return m_value.m_coord;
}

ColorBase & Draught::colorRef()
{
  return m_value.m_color;
}

Draught::KingFlag & Draught::kingFlagRef()
{
  return m_value.m_king;
}
const CoordBase & Draught::coordConstRef() const
{
  return m_value.m_coord;
}

const ColorBase & Draught::colorConstRef() const
{
  return m_value.m_color;
}

const Draught::KingFlag & Draught::kingFlagConstRef() const
{
  return m_value.m_king;
}
