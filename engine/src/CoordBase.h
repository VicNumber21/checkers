#ifndef H_COORD_BASE_H
#define H_COORD_BASE_H

namespace Checkers
{
  namespace Engine
  {
    class CoordBase
    {
    public:
      class ErrorNoValue
      {
      };

      class ErrorIntWrongCoord
      {
      public:
        ErrorIntWrongCoord(int aX, int aY);

      public:
        int m_x;
        int m_y;
      };

      class ErrorCharWrongCoord
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

      void set(char aLetter, char aDigit);
      void set(int aX, int aY);

      bool operator<(const CoordBase &aCoord) const;
      bool operator==(const CoordBase &aCoord) const;
      bool operator!=(const CoordBase &aCoord) const;
      bool operator>(const CoordBase &aCoord) const;

    protected:
      enum
      {
        ENoValue = 0x40
      };

    protected:
      unsigned char value() const;
      void setValue(unsigned char aNewValue);

    private:
      unsigned char m_value;
    };
  };
};

#endif //H_COORD_BASE_H
