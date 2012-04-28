#include "FramedBoardView.h"
#include "RulesOfGame.h"

using namespace Checkers::ConsoleUi;
using namespace Checkers::Engine;


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

std::string FramedBoardView::flushLine(int aN)
{
  std::string ret;
  int height = RulesOfGame::BoardBounds::height();

  if(aN < height + 4)
  {
    if(aN == 0 || aN == height + 3)
    {
      ret = letterLine();
    }
    else if(aN == 1 || aN == height + 2)
    {
      ret = topBottomFrame();
    }
    else
    {
      ret = framedLine(aN - 2);
    }
  }

  return ret;
}

std::string FramedBoardView::letterLine() const
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
  std::string ret(" +");
  int countOfEdgeChar = RulesOfGame::BoardBounds::width();

  for(int j = 0; j < countOfEdgeChar; ++j)
    ret += '-';

  ret += "+ ";

  return ret;
}

std::string FramedBoardView::framedLine(int aN)
{
  std::string ret;

  int height = RulesOfGame::BoardBounds::height();
  int i = (rotation() == BoardView::ERotation0) ? (height - 1 - aN) : aN;

  ret += RulesOfGame::BoardBounds::lineName(i);
  ret += '|';

  if(aN == 0)
  {
    ret += m_BoardView.firstLine();
  }
  else
  {
    ret += m_BoardView.nextLine();
  }

  ret += '|';
  ret += RulesOfGame::BoardBounds::lineName(i);

  return ret;
}
