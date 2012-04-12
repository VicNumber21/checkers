#include "Color.h"

using namespace Checkers::Engine;


Color::Color(const Color &aColor)
{
  setValue(aColor.value());
}

Color::Color(const ColorBase &aColor)
{
  setValue(static_cast<const Color &>(aColor).value());
}

Color::Color(Color::Values aColor)
{
  setValue(aColor);
}
