#include "BoardView.h"
#include "Board.h"
#include "RulesOfGame.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;
using namespace Checkers::ConsoleUi;


const char whiteSquareChar = '#';
const char blackSquareChar = ' ';

const char whiteDraught = 'w';
const char whiteKingDraught = 'W';

const char blackDraught = 'b';
const char blackKingDraught = 'B';

BoardView::BoardView()
  : m_Board(0)
  , m_Rotation(ERotation0)
  , m_CurrentLine(0)
{
}

BoardView::BoardView(const Engine::Board &aBoard, Rotation aRotation)
  : m_Board(&aBoard)
  , m_Rotation(aRotation)
  , m_CurrentLine(0)
{
}

void BoardView::setBoard(const Engine::Board &aBoard)
{
  m_Board = &aBoard;
}

BoardView::Rotation BoardView::rotation() const
{
  return m_Rotation;
}

void BoardView::setRotation(Rotation aRotation)
{
  m_Rotation = aRotation;
}

std::string BoardView::firstLine()
{
  m_CurrentLine = 0;
  return flushLine(m_CurrentLine);
}

std::string BoardView::nextLine()
{
  return flushLine(++m_CurrentLine);
}

std::string BoardView::flushWhole()
{
  std::string ret;

  for(std::string it = firstLine(); !it.empty(); it = nextLine())
  {
    ret += it += '\n';
  }

  return ret;
}

std::string BoardView::flushLine(int aN) const
{
  std::string ret;

  if(Engine::RulesOfGame::BoardBounds::isLineInBound(aN))
  {
    int height = RulesOfGame::BoardBounds::height();
    int width = RulesOfGame::BoardBounds::width();

    int i = m_Rotation == ERotation0 ? height - 1 - aN : aN;

    for(int m = 0; m < width; ++m)
    {
      int j = m_Rotation == ERotation0 ? m : width - 1 - m;

      if((i + j) % 2)
      {
        ret += whiteSquareChar;
      }
      else if(m_Board)
      {
        Maybe<Draught> ijSquare = m_Board->testSquare(Coord(i,j));

        if(ijSquare.isNothing())
        {
          ret += blackSquareChar;
        }
        else if(ijSquare().color() == Color::EWhite)
        {
          ret += ijSquare().isKing() ? whiteKingDraught : whiteDraught;
        }
        else
        {
          ret += ijSquare().isKing() ? blackKingDraught : blackDraught;
        }
      }
      else
      {
        ret += blackSquareChar;
      }
    }
  }

  return ret;
}

std::ostream & Checkers::ConsoleUi::operator<<(std::ostream &aOut, BoardView &aBoardView)
{
  return aOut << aBoardView.flushWhole();
}

std::ostream & Checkers::ConsoleUi::operator<<(std::ostream &aOut, const Board &aBoard)
{
  BoardView view(aBoard);
  return aOut << view;
}
