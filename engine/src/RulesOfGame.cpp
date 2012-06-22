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

bool RulesOfGame::MoveValidator::isValidCoord(const Engine::Coord &aCoord)
{
  return boardTraits().isBlackSquare(aCoord);
}

bool isValidCoordSequenceInternal(const Coord &aFirst, const Coord &aSecond, int aMinDelta = 1, int aMaxDelta = 2)
{
  CoordDelta delta = aFirst - aSecond;

  return (aFirst != aSecond)
         && RulesOfGame::MoveValidator::isValidCoord(aFirst)
         && RulesOfGame::MoveValidator::isValidCoord(aSecond)
         && (aMinDelta <= delta.distance() && delta.distance() <= aMaxDelta);
}

bool RulesOfGame::MoveValidator::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond)
{
  return isValidCoordSequenceInternal(aFirst, aSecond);
}

bool RulesOfGame::MoveValidator::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, const Engine::Coord &aThird)
{
  const int minDeltaForJump = 2;
  return (aFirst != aThird)
         && isValidCoordSequenceInternal(aFirst, aSecond, minDeltaForJump)
         && isValidCoordSequenceInternal(aSecond, aThird, minDeltaForJump);
}

bool RulesOfGame::MoveValidator::isValidDirection(const Engine::Coord &aFirst, const Engine::Coord &aSecond
                                                  , const Engine::Color &aColor, bool isKing)
{
  //TODO add direct test for it
  CoordDelta delta = aSecond - aFirst;
  bool manValidDirection = (aColor == Color::EBlack)? delta.isNorth(): delta.isSouth();
  return isKing || manValidDirection;
}

PositionAnalyser & RulesOfGame::MoveValidator::positionAnalyser()
{
  static AmericanCheckersPositionAnalyser positionAnalyser;
  return positionAnalyser;
}
