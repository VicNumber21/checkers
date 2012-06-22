#include "PositionAnalyser.h"
#include "Move.h"
#include "Color.h"
#include "CoordDelta.h" //TODO remove it after rework in CoordSequence
#include "RulesOfGame.h" //TODO remove it after rework in CoordSequence
#include "BoardTraits.h" //TODO remove it after rework in CoordSequence

using namespace Checkers::Engine;


void PositionAnalyser::setPosition(const Engine::Board &aBoard)
{
  setPosition(aBoard, Color(Color(Color::EBlack)));
}

Move PositionAnalyser::createMove(const Engine::CoordSequence &aCoordSequence, const Engine::Board &aBoard, bool aUpdateColorIfNeeded)
{
  setPosition(aBoard);
  return createMove(aCoordSequence, aUpdateColorIfNeeded);
}

const PositionAnalyser::MoveList & PositionAnalyser::validMoves(const Engine::Board &aBoard, const Engine::Color &aColor)
{
  setPosition(aBoard, aColor);
  return validMoves();
}

//TODO remove it after rework in CoordSequence
bool isValidCoordSequenceInternal(const Coord &aFirst, const Coord &aSecond, int aMinDelta = 1, int aMaxDelta = 2)
{
  CoordDelta delta = aFirst - aSecond;

  return (aFirst != aSecond)
         && RulesOfGame::boardTraits().isBlackSquare(aFirst)
         && RulesOfGame::boardTraits().isBlackSquare(aSecond)
         && (aMinDelta <= delta.distance() && delta.distance() <= aMaxDelta);
}

bool PositionAnalyser::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond)
{
  return isValidCoordSequenceInternal(aFirst, aSecond);
}

bool PositionAnalyser::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, const Engine::Coord &aThird)
{
  const int minDeltaForJump = 2;
  return (aFirst != aThird)
         && isValidCoordSequenceInternal(aFirst, aSecond, minDeltaForJump)
         && isValidCoordSequenceInternal(aSecond, aThird, minDeltaForJump);
}
