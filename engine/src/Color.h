#ifndef H_COLOR_H
#define H_COLOR_H

namespace Checkers
{
  namespace Engine
  {
    class Color
    {
    public:
      enum Values
      {
        EBlack = 0x00
      , EWhite = 0x80
      };

    public:
      Color(const Color &aColor);
      Color(Color::Values aColor);

      bool operator==(const Color::Values aColor) const;
      bool operator!=(const Color::Values aColor) const;
      bool operator==(const Color &aColor) const;
      bool operator!=(const Color &aColor) const;
      friend bool operator==(Color::Values aColor1, const Color &aColor2);
      friend bool operator!=(Color::Values aColor1, const Color &aColor2);

    private:
      unsigned char m_color;
    };

    bool operator==(Color::Values aColor1, const Color &aColor2);
    bool operator!=(Color::Values aColor1, const Color &aColor2);
  };
};

#endif //H_COLOR_H
