#include "PositionAnalyser.h"
#include "Move.h"

using namespace Checkers::Engine;


Move PositionAnalyser::createMove(const Engine::CoordSequence &aCoorsSequence, const Engine::Board &aBoard)
{
  setPosition(aBoard);
  return createMove(aCoorsSequence);
}

PositionAnalyser::MoveList PositionAnalyser::validMoves(const Engine::Board &aBoard)
{
  setPosition(aBoard);
  return validMoves();
}
