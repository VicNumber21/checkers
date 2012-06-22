#include "AmericanCheckersBoardTraits.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;


int AmericanCheckersBoardTraits::height() const
{
  return 8;
}

int AmericanCheckersBoardTraits::width() const
{
  return 8;
}

char AmericanCheckersBoardTraits::lineName(int aN) const
{
  return isLineInBound(aN) ? ('1' + aN) : charOutOfBoundValue();
}

char AmericanCheckersBoardTraits::columnName(int aM) const
{
  return isColumnInBound(aM) ? ('A' + aM) : charOutOfBoundValue();
}

int AmericanCheckersBoardTraits::lineIndex(char aY) const
{
  int n = aY - '1';
  return isLineInBound(n) ? n : intOutOfBoundValue();
}

int AmericanCheckersBoardTraits::columnIndex(char aX) const
{
  int m = toupper(aX) - 'A';
  return isColumnInBound(m) ? m : intOutOfBoundValue();
}

bool AmericanCheckersBoardTraits::isColumnInBound(int aX) const
{
  return aX >= 0 && aX < width();
}

bool AmericanCheckersBoardTraits::isColumnInBound(char aX) const
{
  return columnIndex(aX) != intOutOfBoundValue();
}

bool AmericanCheckersBoardTraits::isLineInBound(int aY) const
{
  return aY >= 0 && aY < AmericanCheckersBoardTraits::height();
}

bool AmericanCheckersBoardTraits::isLineInBound(char aY) const
{
  return lineIndex(aY) != intOutOfBoundValue();
}

bool AmericanCheckersBoardTraits::isKingLine(int aY, const Engine::Color &aColor) const
{
  //TODO add direct test for it
  return (aColor == Color::EBlack && aY == height() - 1)
         || (aColor == Color::EWhite && aY == 0);
}

bool AmericanCheckersBoardTraits::isKingLine(char aY, const Engine::Color &aColor) const
{
  //TODO add direct test for it
  return isKingLine(lineIndex(aY), aColor);
}

bool AmericanCheckersBoardTraits::isBlackSquare(const Engine::Coord &aCoord) const
{
  return 0 == ((aCoord.x() + aCoord.y()) % 2);
}

bool AmericanCheckersBoardTraits::isWhiteSquare(const Engine::Coord &aCoord) const
{
  return !isBlackSquare(aCoord);
}
