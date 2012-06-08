#include "PositionAnalyser.h"
#include "Move.h"
#include "Color.h"

using namespace Checkers::Engine;


void PositionAnalyser::setPosition(const Engine::Board &aBoard)
{
  setPosition(aBoard, Color(Color(Color::EBlack)));
}

Move PositionAnalyser::createMove(const Engine::CoordSequence &aCoorsSequence, const Engine::Board &aBoard, bool aUpdateColorIfNeeded)
{
  setPosition(aBoard);
  return createMove(aCoorsSequence, aUpdateColorIfNeeded);
}

const PositionAnalyser::MoveList & PositionAnalyser::validMoves(const Engine::Board &aBoard, const Engine::Color &aColor)
{
  setPosition(aBoard, aColor);
  return validMoves();
}
