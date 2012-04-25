#include "CoordBase.h"
#include "RulesOfGame.h"

#include <ctype.h>

using namespace Checkers::Engine;


const int bit_field_length = 3;
const unsigned char coord_clean_mask = (~0) << (2*bit_field_length);


void throwIfWrongCoord(int aX, int aY)
{
  if(!RulesOfGame::BoardBounds::isColumnInBound(aX) || !RulesOfGame::BoardBounds::isLineInBound(aY))
    throw(CoordBase::ErrorIntWrongCoord(aX, aY));
}

void throwIfWrongCoord(char aLetter, char aDigit)
{
  if(!RulesOfGame::BoardBounds::isColumnInBound(aLetter) || !RulesOfGame::BoardBounds::isLineInBound(aDigit))
    throw(CoordBase::ErrorCharWrongCoord(aLetter, aDigit));
}

char compressToChar(int aX, int aY)
{
  return (aX << bit_field_length) | aY;
}

CoordBase::ErrorIntWrongCoord::ErrorIntWrongCoord(int aX, int aY)
  : m_x(aX)
  , m_y(aY)
{
}

CoordBase::ErrorCharWrongCoord::ErrorCharWrongCoord(char aLetter, char aDigit)
  : m_letter(aLetter)
  , m_digit(aDigit)
{
}

int CoordBase::x() const
{
  return value() >> bit_field_length;
}

int CoordBase::y() const
{
  return value() & (~((~0) << bit_field_length));
}

char CoordBase::letter() const
{
  return tolower(RulesOfGame::BoardBounds::columnName(x()));
}

char CoordBase::digit() const
{
  return RulesOfGame::BoardBounds::lineName(y());
}

CoordBase & CoordBase::assign(const CoordBase &aCoord)
{
  setValue(aCoord.value());
  return *this;
}

bool CoordBase::operator<(const CoordBase &aCoord) const
{
  return value() < aCoord.value();
}

bool CoordBase::operator==(const CoordBase &aCoord) const
{
  return value() == aCoord.value();
}

bool CoordBase::operator!=(const CoordBase &aCoord) const
{
  return !(*this == aCoord);
}

bool CoordBase::operator>(const CoordBase &aCoord) const
{
  return value() > aCoord.value();
}

void CoordBase::set(char aLetter, char aDigit)
{
  throwIfWrongCoord(aLetter, aDigit);
  set(RulesOfGame::BoardBounds::columnIndex(aLetter), RulesOfGame::BoardBounds::lineIndex(aDigit));
}

void CoordBase::set(int aX, int aY)
{
  throwIfWrongCoord(aX, aY);
  setValue(compressToChar(aX, aY));
}

unsigned char CoordBase::value() const
{
  return m_value & (~coord_clean_mask);
}

void CoordBase::setValue(unsigned char aNewValue)
{
  m_value &= coord_clean_mask;
  m_value |= (aNewValue & ~coord_clean_mask);
}
