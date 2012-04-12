#include "CoordBase.h"

using namespace Checkers::Engine;


const char low_letter_bound = 'a';
const char top_letter_bound = 'h';

const char low_digit_bound = '1';
const char top_digit_bound = '8';

const int low_int_bound = 0;
const int top_int_bound = 8;

const int bit_field_length = 3;
const unsigned char coord_clean_mask = (~0) << (2*bit_field_length);


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
    throw(CoordBase::ErrorIntWrongCoord(aX, aY));
}

void throwIfWrongCoord(char aLetter, char aDigit)
{
  if(aLetter < low_letter_bound || aLetter > top_letter_bound || aDigit < low_digit_bound || aDigit > top_digit_bound)
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
  return low_letter_bound + x();
}

char CoordBase::digit() const
{
  return low_digit_bound + y();
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
  set(letterToX(aLetter), digitToY(aDigit));
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
