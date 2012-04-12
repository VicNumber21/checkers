#ifndef H_COLOR_H
#define H_COLOR_H

#include "ColorBase.h"


namespace Checkers
{
  namespace Engine
  {
    class Color : public ColorBase
    {
    public:
      Color(const Color &aColor);
      Color(Color::Values aColor);
    };
  };
};

#endif //H_COLOR_H
