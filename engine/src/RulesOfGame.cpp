#include "RulesOfGame.h"
#include "Coord.h"
#include "Color.h"
#include "Board.h"

#include <ctype.h>
#include <stdlib.h>

using namespace Checkers::Engine;


const int intOutOfBound = -1;
const char charOutOfBound = '!';

AmericanCheckersActionFactory RulesOfGame::MoveValidator::m_action_factory;

int RulesOfGame::BoardBounds::height()
{
  return 8;
}

int RulesOfGame::BoardBounds::width()
{
  return 8;
}

char RulesOfGame::BoardBounds::lineName(int aN)
{
  return RulesOfGame::BoardBounds::isLineInBound(aN) ? ('1' + aN) : charOutOfBound;
}

char RulesOfGame::BoardBounds::columnName(int aM)
{
  return RulesOfGame::BoardBounds::isColumnInBound(aM) ? ('A' + aM) : charOutOfBound;
}

int RulesOfGame::BoardBounds::lineIndex(char aY)
{
  int n = aY - '1';
  return RulesOfGame::BoardBounds::isLineInBound(n) ? n : intOutOfBound;
}

int RulesOfGame::BoardBounds::columnIndex(char aX)
{
  int m = toupper(aX) - 'A';
  return RulesOfGame::BoardBounds::isColumnInBound(m) ? m : intOutOfBound;
}

bool RulesOfGame::BoardBounds::isColumnInBound(int aX)
{
  return aX >= 0 && aX < RulesOfGame::BoardBounds::width();
}

bool RulesOfGame::BoardBounds::isColumnInBound(char aX)
{
  return RulesOfGame::BoardBounds::columnIndex(aX) != intOutOfBound;
}

bool RulesOfGame::BoardBounds::isLineInBound(int aY)
{
  return aY >= 0 && aY < RulesOfGame::BoardBounds::height();
}

bool RulesOfGame::BoardBounds::isLineInBound(char aY)
{
  return RulesOfGame::BoardBounds::lineIndex(aY) != intOutOfBound;
}

bool RulesOfGame::BoardBounds::isKingLine(int aY, const Engine::Color &aColor)
{
  //TODO add direct test for it
  return (aColor == Color::EBlack && aY == RulesOfGame::BoardBounds::height() - 1)
         || (aColor == Color::EWhite && aY == 0);
}

bool RulesOfGame::BoardBounds::isKingLine(char aY, const Engine::Color &aColor)
{
  //TODO add direct test for it
  return RulesOfGame::BoardBounds::isKingLine(RulesOfGame::BoardBounds::lineIndex(aY), aColor);
}

bool RulesOfGame::MoveValidator::isValidCoord(const Engine::Coord &aCoord)
{
  //TODO rework it to isBlackSquare() in BoardUtility
  return 0 == ((aCoord.x() + aCoord.y()) % 2);
}

bool RulesOfGame::MoveValidator::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, bool isJump)
{
  int deltaX = abs(aFirst.x() - aSecond.x());
  int deltaY = abs(aFirst.y() - aSecond.y());
  int expectedDelta = isJump ? 2 : 1;

  //TODO rework as IsOnSameDiagonal() && isDeltaInExpectedRange() from BoardUtility
  return isValidCoord(aFirst) && isValidCoord(aSecond) && (deltaX == expectedDelta) && (deltaY == expectedDelta);
}

bool RulesOfGame::MoveValidator::isValidDirection(const Engine::Coord &aFirst, const Engine::Coord &aSecond
                                                  , const Engine::Color &aColor, bool isKing)
{
  //TODO add direct test for it
  int deltaY = aSecond.y() - aFirst.y();
  int validDirectionSign = (aColor == Color::EBlack)? 1 : -1;
  return isKing || (deltaY * validDirectionSign > 0);
}

bool RulesOfGame::MoveValidator::doesJumpExist(const Engine::Board &aBoard, const Engine::Color &aColor)
{
  //TODO move delta code & logic into class (probably make an iterator)
  //TODO add direct test for it
  const int deltaX[4] = {-1, 1, 1, -1};
  const int deltaY[4] = {1, 1, -1, -1};

  for(Board::Iterator it = aBoard.begin(); it != aBoard.end(); ++it)
  {
    if(it->color() == aColor)
    {
      try
      {
        int firstDeltaIndex = it->isKing()? 0 : aColor == Color::EBlack ? 0 : 2;
        int lastDeltaIndex = it->isKing()? 3 : aColor == Color::EBlack ? 1 : 3;

        for(int deltaIndex = firstDeltaIndex; deltaIndex <= lastDeltaIndex; ++deltaIndex)
        {
          Coord jumpedCoord(it->coord().x() + deltaX[deltaIndex], it->coord().y() + deltaY[deltaIndex]);
          Coord jumpToCoord(it->coord().x() + 2 * deltaX[deltaIndex], it->coord().y() + 2 * deltaY[deltaIndex]);
          Maybe<Draught> jumpedDraught = aBoard.testSquare(jumpedCoord);
          Maybe<Draught> jumpToDraught = aBoard.testSquare(jumpToCoord);

          if(!jumpedDraught.isNothing() && jumpedDraught().color() != aColor && jumpToDraught.isNothing())
          {
            return true;
          }
        }
      }
      catch(Coord::ErrorIntWrongCoord e)
      {
        continue;
      }
    }
  }

  return false;
}

ActionAtBoard::Ptr RulesOfGame::MoveValidator::transformIntoActions(const Engine::Board &aBoard, const Engine::Move &aMove)
{
  return actionFactory().createAction(aBoard, aMove);
}

const AmericanCheckersActionFactory & RulesOfGame::MoveValidator::actionFactory()
{
  return m_action_factory;
}
