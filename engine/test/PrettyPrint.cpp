#include "PrettyPrint.h"
#include "Board.h"
#include "Coord.h"
#include "FramedBoardView.h"

using namespace Checkers::Engine;

std::ostream & operator<<(std::ostream &aOut, const Board &aBoard)
{
  Checkers::ConsoleUi::FramedBoardView view(aBoard);
  return aOut << std::endl << view;
}

std::ostream & operator<<(std::ostream &aOut, const Coord &aCoord)
{
  return aOut << std::endl << "(" << aCoord.letter() << ", " << aCoord.digit() << ")";
}
