#ifndef H_PRETTY_PRINT_H
#define H_PRETTY_PRINT_H

#include <ostream>


namespace Checkers
{
  namespace Engine
  {
    class Board;
    class Coord;
    class CoordDelta;
  }
}

std::ostream & operator<<(std::ostream &aOut, const Checkers::Engine::Board &aBoard);
std::ostream & operator<<(std::ostream &aOut, const Checkers::Engine::Coord &aCoord);
std::ostream & operator<<(std::ostream &aOut, const Checkers::Engine::CoordDelta &aDelta);

#endif //H_PRETTY_PRINT_H
