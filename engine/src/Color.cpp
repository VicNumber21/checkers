#include "Color.h"

using namespace Checkers::Engine;


Color::Color(const Color &aColor)
  : m_color(aColor.m_color)
{
}

Color::Color(Color::Values aColor)
  : m_color(aColor)
{
}

bool Color::operator==(const Color::Values aColor) const
{
  return m_color == aColor;
}

bool Color::operator!=(const Color::Values aColor) const
{
  return !((*this) == aColor);
}

bool Color::operator==(const Color &aColor) const
{
  return m_color == aColor.m_color;
}

bool Color::operator!=(const Color &aColor) const
{
  return !((*this) == aColor);
}

bool Checkers::Engine::operator==(Color::Values aColor1, const Color &aColor2)
{
  return aColor2 == aColor1;
}

bool Checkers::Engine::operator!=(Color::Values aColor1, const Color &aColor2)
{
  return aColor2 != aColor1;
}
