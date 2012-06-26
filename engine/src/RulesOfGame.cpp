#include "RulesOfGame.h"
#include "RulesOfGameManager.h"

using namespace Checkers::Engine;


const BoardTraits & RulesOfGame::boardTraits()
{
  return RulesOfGameManager::instance().currentBoardTraits();
}

PositionAnalyser & RulesOfGame::positionAnalyser()
{
  return RulesOfGameManager::instance().currentPositionAnalyser();
}
