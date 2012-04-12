#ifndef H_COLOR_BASE_H
#define H_COLOR_BASE_H

#include "BitFlag.h"

namespace Checkers
{
  namespace Engine
  {
    class ColorBase
    {
    public:
      enum Values
      {
        EBlack
      , EWhite
      };

    public:
      ColorBase & assign(const ColorBase &aColor);

      bool operator==(ColorBase::Values aColor) const;
      bool operator!=(ColorBase::Values aColor) const;
      bool operator==(const ColorBase &aColor) const;
      bool operator!=(const ColorBase &aColor) const;
      friend bool operator==(ColorBase::Values aColor1, const ColorBase &aColor2);
      friend bool operator!=(ColorBase::Values aColor1, const ColorBase &aColor2);

    protected:
      ColorBase::Values value() const;
      void setValue(ColorBase::Values aNewValue);

    private:
      BitFlag<unsigned char, 0x80> m_value;
    };

    bool operator==(ColorBase::Values aColor1, const ColorBase &aColor2);
    bool operator!=(ColorBase::Values aColor1, const ColorBase &aColor2);
  };
};

#endif //H_COLOR_BASE_H
