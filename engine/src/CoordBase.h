#ifndef H_COORD_BASE_H
#define H_COORD_BASE_H

#include "Error.h"

namespace Checkers
{
  namespace Engine
  {
    class CoordBase
    {
    public:
      class ErrorIntWrongCoord : public Engine::Error
      {
      public:
        ErrorIntWrongCoord(int aX, int aY);

      public:
        int m_x;
        int m_y;
      };

      class ErrorCharWrongCoord : public Engine::Error
      {
      public:
        ErrorCharWrongCoord(char aLetter, char aDigit);

      public:
        char m_letter;
        char m_digit;
      };

    public:
      int x() const;
      int y() const;
      char letter() const;
      char digit() const;

      CoordBase & assign(const CoordBase &aCoord);

      bool operator<(const CoordBase &aCoord) const;
      bool operator==(const CoordBase &aCoord) const;
      bool operator!=(const CoordBase &aCoord) const;
      bool operator>(const CoordBase &aCoord) const;

    protected:
      void set(char aLetter, char aDigit);
      void set(int aX, int aY);

      unsigned char value() const;
      void setValue(unsigned char aNewValue);

    private:
      unsigned char m_value;
    };
  };
};

#endif //H_COORD_BASE_H
