#include "Coord.h"

using namespace Checkers::Engine;


Coord::Coord()
{
  setValue(CoordBase::ENoValue);
}

Coord::Coord(const Coord &aCoord)
{
  setValue(aCoord.value());
}

Coord::Coord(char aLetter, char aDigit)
{
  set(aLetter, aDigit);
}

Coord::Coord(int aX, int aY)
{
  set(aX, aY);
}
