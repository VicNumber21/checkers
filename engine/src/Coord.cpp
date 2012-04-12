#include "Coord.h"

using namespace Checkers::Engine;


Coord::Coord(const Coord &aCoord)
{
  setValue(aCoord.value());
}

Coord::Coord(const CoordBase &aCoord)
{
  setValue(static_cast<const Coord &>(aCoord).value());
}

Coord::Coord(char aLetter, char aDigit)
{
  set(aLetter, aDigit);
}

Coord::Coord(int aX, int aY)
{
  set(aX, aY);
}
