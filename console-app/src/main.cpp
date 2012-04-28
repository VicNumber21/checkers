#include <iostream>

#include "FramedBoardView.h"
#include "Board.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::ConsoleUi;


int main()
{
  Checkers::Engine::Board board;
  FramedBoardView framedBoardView(board);

  std::cout << std::endl << framedBoardView << std::endl;

  return 0;
}
