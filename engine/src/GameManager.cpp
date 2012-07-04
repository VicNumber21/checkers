#include "GameManager.h"
#include "Move.h"
#include "Draught.h"
#include "Color.h"

#include <algorithm>
#include <time.h>

using namespace Checkers::Engine;


GameManager & GameManager::instance()
{
  static GameManager gameManager;
  return gameManager;
}

GameManager::GameManager()
{
  srand(time(0));
}

void GameManager::setCurrentBoard(const Board &aBoard)
{
  if(aBoard.count() == 0) //TODO add isEmpty() to Board 
    m_current_board = initialBoard();
  else
    m_current_board = aBoard;
}

const Board & GameManager::currentBoard() const
{
  return m_current_board;
}

void GameManager::applyMove(const Move &aMove)
{
  //TODO need to check color here
  if(m_current_board == aMove.from())
    m_current_board = aMove.to();
  else
    throw GameManager::Error();
}

Board GameManager::initialBoard() const
{
  Board b;

  for(int i = 0; i < 3*8/2; ++i)
  {
    int rowBlack = i / 4;
    int rowWhite = rowBlack + 5;
    int colBlack = (i % 4) * 2;
    int colWhite = colBlack + 1;

    if(rowBlack % 2 == 1)
      std::swap(colBlack, colWhite);

    b.put(Draught(Coord(colBlack, rowBlack), Color::EBlack));
    b.put(Draught(Coord(colWhite, rowWhite), Color::EWhite));
  }

  return b;
}
