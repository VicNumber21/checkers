#include "FramedBoardView.h"
#include "RulesOfGame.h"

using namespace Checkers::ConsoleUi;
using namespace Checkers::Engine;


const char frameCornerChar = '+';
const char frameVerticalLineChar = '|';
const char frameHorizontalLineChar = '-';

FramedBoardView::FramedBoardView()
  : m_BoardView()
{
}

FramedBoardView::FramedBoardView(const Board &aBoard, BoardView::Rotation aRotation)
  : m_BoardView(aBoard, aRotation)
{
}

void FramedBoardView::setBoard(const Board &aBoard)
{
  m_BoardView.setBoard(aBoard);
}

BoardView::Rotation FramedBoardView::rotation() const
{
  return m_BoardView.rotation();
}

void FramedBoardView::setRotation(BoardView::Rotation aRotation)
{
  m_BoardView.setRotation(aRotation);
}

std::string FramedBoardView::flushRow(int aN)
{
  std::string ret;
  int height = RulesOfGame::BoardBounds::height();

  if(aN < height + 4)
  {
    if(aN == 0 || aN == height + 3)
    {
      ret = letterRow();
    }
    else if(aN == 1 || aN == height + 2)
    {
      ret = topBottomFrame();
    }
    else
    {
      ret = framedRow(aN - 2);
    }
  }

  return ret;
}

std::string FramedBoardView::letterRow() const
{
  std::string ret("  ");
  int width = RulesOfGame::BoardBounds::width();

  for(int m = 0; m < width; ++m)
  {
    int j = (rotation() == BoardView::ERotation0) ? m : (width - 1 - m);
    ret += RulesOfGame::BoardBounds::columnName(j);
  }

  ret += "  ";

  return ret;
}

std::string FramedBoardView::topBottomFrame() const
{
  std::string ret(" ");
  ret += frameCornerChar;

  int countOfEdgeChar = RulesOfGame::BoardBounds::width();

  for(int j = 0; j < countOfEdgeChar; ++j)
    ret += frameHorizontalLineChar;

  ret += frameCornerChar;
  ret += " ";

  return ret;
}

std::string FramedBoardView::framedRow(int aN)
{
  std::string ret;

  int height = RulesOfGame::BoardBounds::height();
  int i = (rotation() == BoardView::ERotation0) ? (height - 1 - aN) : aN;

  ret += RulesOfGame::BoardBounds::rowName(i);
  ret += frameVerticalLineChar;

  if(aN == 0)
  {
    ret += m_BoardView.firstRow();
  }
  else
  {
    ret += m_BoardView.nextRow();
  }

  ret += frameVerticalLineChar;
  ret += RulesOfGame::BoardBounds::rowName(i);

  return ret;
}
