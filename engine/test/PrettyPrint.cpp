#include "PrettyPrint.h"
#include "Board.h"
#include "Coord.h"
#include "CoordDelta.h"
#include "CoordSequence.h"
#include "FramedBoardView.h"

using namespace Checkers::Engine;

std::ostream & operator<<(std::ostream &aOut, const Board &aBoard)
{
  Checkers::ConsoleUi::FramedBoardView view(aBoard);
  return aOut << std::endl << view;
}

std::ostream & operator<<(std::ostream &aOut, const Coord &aCoord)
{
  return aOut << std::endl << "Coord(" << aCoord.letter() << ", " << aCoord.digit() << ")";
}

std::ostream & operator<<(std::ostream &aOut, const CoordDelta &aDelta)
{
  return aOut << std::endl << "CoordDelta(" << aDelta.x() << ", " << aDelta.y() << ")";
}

std::ostream & operator<<(std::ostream &aOut, const Checkers::Engine::CoordSequence &aCoordSequence)
{
  aOut << std::endl << "CoordSequence(";

  for(CoordSequence::Iterator it = aCoordSequence.begin(); it != aCoordSequence.end(); ++it)
  {
    if(it != aCoordSequence.begin())
    {
      aOut << '-';
    }

    aOut << *it;
  }

  return aOut << ')';
}
