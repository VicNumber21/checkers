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

char AmericanCheckersBoardTraits::rowName(int aN) const
{
  return isRowInBound(aN) ? ('1' + aN) : charOutOfBoundValue();
}

char AmericanCheckersBoardTraits::columnName(int aM) const
{
  return isColumnInBound(aM) ? ('A' + aM) : charOutOfBoundValue();
}

int AmericanCheckersBoardTraits::rowIndex(char aY) const
{
  int n = aY - '1';
  return isRowInBound(n) ? n : intOutOfBoundValue();
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

bool AmericanCheckersBoardTraits::isRowInBound(int aY) const
{
  return aY >= 0 && aY < AmericanCheckersBoardTraits::height();
}

bool AmericanCheckersBoardTraits::isRowInBound(char aY) const
{
  return rowIndex(aY) != intOutOfBoundValue();
}

bool AmericanCheckersBoardTraits::isKingRow(int aY, const Engine::Color &aColor) const
{
  return (aColor == Color::EBlack && aY == height() - 1)
         || (aColor == Color::EWhite && aY == 0);
}

bool AmericanCheckersBoardTraits::isKingRow(char aY, const Engine::Color &aColor) const
{
  return isKingRow(rowIndex(aY), aColor);
}

bool AmericanCheckersBoardTraits::isBlackSquare(const Engine::Coord &aCoord) const
{
  return 0 == ((aCoord.x() + aCoord.y()) % 2);
}

bool AmericanCheckersBoardTraits::isWhiteSquare(const Engine::Coord &aCoord) const
{
  return !isBlackSquare(aCoord);
}
