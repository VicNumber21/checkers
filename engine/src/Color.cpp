#include "Color.h"

using namespace Checkers::Engine;


Color::Color(const Color &aColor)
{
  setValue(aColor.value());
}

Color::Color(Color::Values aColor)
{
  setValue(aColor);
}
