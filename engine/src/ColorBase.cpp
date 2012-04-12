#include "ColorBase.h"

using namespace Checkers::Engine;


ColorBase & ColorBase::assign(const ColorBase &aColor)
{
  setValue(aColor.value());
  return *this;
}

bool ColorBase::operator==(ColorBase::Values aColor) const
{
  return value() == aColor;
}

bool ColorBase::operator!=(ColorBase::Values aColor) const
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

ColorBase::Values ColorBase::value() const
{
  return m_value() ? ColorBase::EWhite : ColorBase::EBlack;
}

void ColorBase::setValue(ColorBase::Values aNewValue)
{
  m_value.set(ColorBase::EWhite == aNewValue);
}

bool Checkers::Engine::operator==(ColorBase::Values aColor1, const ColorBase &aColor2)
{
  return aColor2 == aColor1;
}

bool Checkers::Engine::operator!=(ColorBase::Values aColor1, const ColorBase &aColor2)
{
  return aColor2 != aColor1;
}
