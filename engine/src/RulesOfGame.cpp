#include "RulesOfGame.h"
#include "Coord.h"

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

ActionAtBoard::Ptr RulesOfGame::MoveValidator::transformIntoActions(const Engine::Board &aBoard, const Engine::Move &aMove)
{
  (void) aBoard;
  (void) aMove;

  ActionAtBoard::Ptr ret;
  return ret;
}
