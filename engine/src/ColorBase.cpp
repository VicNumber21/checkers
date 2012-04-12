#include "ColorBase.h"

using namespace Checkers::Engine;


const unsigned char color_mask = 0x80;

ColorBase & ColorBase::assign(const ColorBase &aColor)
{
  setValue(aColor.value());
  return *this;
}

bool ColorBase::operator==(const ColorBase::Values aColor) const
{
  return value() == aColor;
}

bool ColorBase::operator!=(const ColorBase::Values aColor) const
{
  return !((*this) == aColor);
}

bool ColorBase::operator==(const ColorBase &aColor) const
{
  return value() == aColor.value();
}

bool ColorBase::operator!=(const ColorBase &aColor) const
{
  return !((*this) == aColor);
}

unsigned char ColorBase::value() const
{
  return m_value & color_mask;
}

void ColorBase::setValue(unsigned char aNewValue)
{
  m_value &= ~color_mask;
  m_value |= aNewValue & color_mask;
}

bool Checkers::Engine::operator==(ColorBase::Values aColor1, const ColorBase &aColor2)
{
  return aColor2 == aColor1;
}

bool Checkers::Engine::operator!=(ColorBase::Values aColor1, const ColorBase &aColor2)
{
  return aColor2 != aColor1;
}
