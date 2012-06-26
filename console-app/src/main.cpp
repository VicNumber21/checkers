#include <iostream>

#include "RulesOfGameManager.h"
#include "RulesOfGameInstances.h"
#include "FramedBoardView.h"
#include "Board.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;
using namespace Checkers::ConsoleUi;


int main()
{
  RulesOfGameManager::instance().append(RulesOfGameInstanceInterface::Ptr(new AmericanCheckersRulesOfGame), true);

  Board board;
  FramedBoardView framedBoardView(board);

  std::cout << std::endl << framedBoardView << std::endl;

  return 0;
}
