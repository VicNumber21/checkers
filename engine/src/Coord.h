#ifndef H_COORD_H
#define H_COORD_H

namespace Checkers
{
  namespace Engine
  {
    class Coord
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
      Coord();
      Coord(const Coord &aCoord);
      Coord(char aLetter, char aDigit);
      Coord(int aX, int aY);

      int x() const;
      int y() const;
      char letter() const;
      char digit() const;

      void set(char aLetter, char aDigit);
      void set(int aX, int aY);

      bool operator<(const Coord &aCoord) const;
      bool operator==(const Coord &aCoord) const;
      bool operator>(const Coord &aCoord) const;

    private:
      enum
      {
        ENoValue = 255
      };

    private:
      unsigned char m_coord;
    };
  };
};

#endif //H_COORD_H
