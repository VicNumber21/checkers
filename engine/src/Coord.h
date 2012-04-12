#ifndef H_COORD_H
#define H_COORD_H

#include "CoordBase.h"


namespace Checkers
{
  namespace Engine
  {
    class Coord : public CoordBase
    {
    public:
      Coord();
      Coord(const Coord &aCoord);
      Coord(char aLetter, char aDigit);
      Coord(int aX, int aY);
    };
  };
};

#endif //H_COORD_H
