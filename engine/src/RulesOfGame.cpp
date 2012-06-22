#include "RulesOfGame.h"
#include "Coord.h"
#include "CoordDelta.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "AmericanCheckersPositionAnalyser.h"
#include "AmericanCheckersBoardTraits.h"

#include <ctype.h>
#include <stdlib.h>

using namespace Checkers::Engine;


const BoardTraits & RulesOfGame::boardTraits()
{
  static AmericanCheckersBoardTraits boardTraits;
  return boardTraits;
}

PositionAnalyser & RulesOfGame::positionAnalyser()
{
  static AmericanCheckersPositionAnalyser positionAnalyser;
  return positionAnalyser;
}
