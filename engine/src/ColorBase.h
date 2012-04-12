#ifndef H_COLOR_BASE_H
#define H_COLOR_BASE_H

namespace Checkers
{
  namespace Engine
  {
    class ColorBase
    {
    public:
      enum Values
      {
        EBlack = 0x00
      , EWhite = 0x80
      };

    public:
      ColorBase & assign(const ColorBase &aColor);

      bool operator==(const ColorBase::Values aColor) const;
      bool operator!=(const ColorBase::Values aColor) const;
      bool operator==(const ColorBase &aColor) const;
      bool operator!=(const ColorBase &aColor) const;
      friend bool operator==(ColorBase::Values aColor1, const ColorBase &aColor2);
      friend bool operator!=(ColorBase::Values aColor1, const ColorBase &aColor2);

    protected:
      unsigned char value() const;
      void setValue(unsigned char aNewValue);

    private:
      unsigned char m_value;
    };

    bool operator==(ColorBase::Values aColor1, const ColorBase &aColor2);
    bool operator!=(ColorBase::Values aColor1, const ColorBase &aColor2);
  };
};

#endif //H_COLOR_BASE_H
