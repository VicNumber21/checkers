#include "RulesOfGame.h"
#include "Coord.h"
#include "CoordDelta.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "AmericanCheckersPositionAnalyser.h"

#include <ctype.h>
#include <stdlib.h>

using namespace Checkers::Engine;


const int intOutOfBound = -1;
const char charOutOfBound = '!';

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

bool isValidCoordSequenceInternal(const Coord &aFirst, const Coord &aSecond, int aMinDelta = 1, int aMaxDelta = 2)
{
  CoordDelta delta = aFirst - aSecond;

  return (aFirst != aSecond)
         && RulesOfGame::MoveValidator::isValidCoord(aFirst)
         && RulesOfGame::MoveValidator::isValidCoord(aSecond)
         && (aMinDelta <= delta.distance() && delta.distance() <= aMaxDelta);
}

bool RulesOfGame::MoveValidator::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond)
{
  return isValidCoordSequenceInternal(aFirst, aSecond);
}

bool RulesOfGame::MoveValidator::isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, const Engine::Coord &aThird)
{
  const int minDeltaForJump = 2;
  return (aFirst != aThird)
         && isValidCoordSequenceInternal(aFirst, aSecond, minDeltaForJump)
         && isValidCoordSequenceInternal(aSecond, aThird, minDeltaForJump);
}

bool RulesOfGame::MoveValidator::isValidDirection(const Engine::Coord &aFirst, const Engine::Coord &aSecond
                                                  , const Engine::Color &aColor, bool isKing)
{
  //TODO add direct test for it
  CoordDelta delta = aSecond - aFirst;
  bool manValidDirection = (aColor == Color::EBlack)? delta.isNorth(): delta.isSouth();
  return isKing || manValidDirection;
}

bool RulesOfGame::MoveValidator::doesJumpExist(const Engine::Board &aBoard, const Engine::Draught &aDraught)
{
  //TODO add direct test for it
  CoordDelta::Direction directions[4] = {
                          CoordDelta::ENorthWest
                        , CoordDelta::ENorthEast
                        , CoordDelta::ESouthEast
                        , CoordDelta::ESouthWest
                        };

  int firstDirectionIndex = aDraught.isKing()? 0 : aDraught.color() == Color::EBlack ? 0 : 2;
  int lastDirectionIndex = aDraught.isKing()? 3 : aDraught.color() == Color::EBlack ? 1 : 3;

  bool ret = false;

  for(int directionIndex = firstDirectionIndex; directionIndex <= lastDirectionIndex; ++directionIndex)
  {
    try
    {
      Coord jumpToCoord = aDraught.coord() + CoordDelta(directions[directionIndex], 2);
      Coord jumpedCoord = aDraught.coord() + CoordDelta(directions[directionIndex], 1);

      Maybe<Draught> jumpedDraught = aBoard.testSquare(jumpedCoord);
      Maybe<Draught> jumpToDraught = aBoard.testSquare(jumpToCoord);

      if(!jumpedDraught.isNothing() && jumpedDraught().color() != aDraught.color() && jumpToDraught.isNothing())
      {
        ret = true;
        break;
      }
    }
    catch(Coord::ErrorIntWrongCoord e)
    {
      continue;
    }
  }

  return ret;
}

bool RulesOfGame::MoveValidator::doesJumpExist(const Engine::Board &aBoard, const Engine::Color &aColor)
{
  bool ret = false;

  for(Board::Iterator it = aBoard.begin(); it != aBoard.end(); ++it)
  {
    if(it->color() == aColor)
    {
      if(doesJumpExist(aBoard, *it))
      {
        ret = true;
        break;
      }
    }
  }

  return ret;
}

PositionAnalyser & RulesOfGame::MoveValidator::positionAnalyser()
{
  static AmericanCheckersPositionAnalyser postionAnalyser;
  return postionAnalyser;
}
