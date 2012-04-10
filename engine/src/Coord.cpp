#include "Coord.h"

using namespace Checkers::Engine;


const char low_letter_bound = 'a';
const char top_letter_bound = 'h';

const char low_digit_bound = '1';
const char top_digit_bound = '8';

const int low_int_bound = 0;
const int top_int_bound = 8;

const int bit_field_length = 3;


int letterToX(char aLetter)
{
  return aLetter - low_letter_bound;
}

int digitToY(char aDigit)
{
  return aDigit - low_digit_bound;
}

void throwIfWrongCoord(int aX, int aY)
{
  if(aX < low_int_bound || aX > top_int_bound || aY < low_int_bound || aY > top_int_bound)
    throw(Coord::ErrorIntWrongCoord(aX, aY));
}

void throwIfWrongCoord(char aLetter, char aDigit)
{
  if(aLetter < low_letter_bound || aLetter > top_letter_bound || aDigit < low_digit_bound || aDigit > top_digit_bound)
    throw(Coord::ErrorCharWrongCoord(aLetter, aDigit));
}

char compressToChar(int aX, int aY)
{
  return (aX << bit_field_length) | aY;
}

Coord::ErrorIntWrongCoord::ErrorIntWrongCoord(int aX, int aY)
  : m_x(aX)
  , m_y(aY)
{
}

Coord::ErrorCharWrongCoord::ErrorCharWrongCoord(char aLetter, char aDigit)
  : m_letter(aLetter)
  , m_digit(aDigit)
{
}

Coord::Coord()
  : m_coord(ENoValue)
{
}

Coord::Coord(const Coord &aCoord)
  : m_coord(aCoord.m_coord)
{
}

Coord::Coord(char aLetter, char aDigit)
  : m_coord(compressToChar(letterToX(aLetter), digitToY(aDigit)))
{
  throwIfWrongCoord(aLetter, aDigit);
}

Coord::Coord(int aX, int aY)
  : m_coord(compressToChar(aX, aY))
{
  throwIfWrongCoord(aX, aY);
}

int Coord::x() const
{
  if(m_coord == Coord::ENoValue)
    throw(Coord::ErrorNoValue());

  return m_coord >> bit_field_length;
}

int Coord::y() const
{
  if(m_coord == Coord::ENoValue)
    throw(Coord::ErrorNoValue());

  return m_coord & (~((~0) << bit_field_length));
}

char Coord::letter() const
{
  return low_letter_bound + x();
}

char Coord::digit() const
{
  return low_digit_bound + y();
}

void Coord::set(char aLetter, char aDigit)
{
  throwIfWrongCoord(aLetter, aDigit);
  set(letterToX(aLetter), digitToY(aDigit));
}

void Coord::set(int aX, int aY)
{
  throwIfWrongCoord(aX, aY);
  m_coord = compressToChar(aX, aY);
}

bool Coord::operator<(const Coord &aCoord) const
{
  return m_coord < aCoord.m_coord;
}

bool Coord::operator==(const Coord &aCoord) const
{
  return m_coord == aCoord.m_coord;
}

bool Coord::operator>(const Coord &aCoord) const
{
  return m_coord > aCoord.m_coord;
}
