#ifndef H_BOARD_TRAITS_H
#define H_BOARD_TRAITS_H


namespace Checkers
{
  namespace Engine
  {
    class Coord;
    class Color;

    class BoardTraits
    {
    public:
      inline int intOutOfBoundValue() const {return -1;}
      inline char charOutOfBoundValue() const {return '!';}

    public:
      virtual int height() const = 0;
      virtual int width() const = 0;

      virtual char rowName(int aN) const = 0;
      virtual char columnName(int aM) const = 0;

      virtual int rowIndex(char aY) const = 0;
      virtual int columnIndex(char aX) const = 0;

      virtual bool isColumnInBound(int aX) const = 0;
      virtual bool isColumnInBound(char aX) const = 0;

      virtual bool isRowInBound(int aY) const = 0;
      virtual bool isRowInBound(char aY) const = 0;

      virtual bool isKingRow(int aY, const Engine::Color &aColor) const = 0;
      virtual bool isKingRow(char aY, const Engine::Color &aColor) const = 0;

      virtual bool isBlackSquare(const Engine::Coord &aCoord) const = 0;
      virtual bool isWhiteSquare(const Engine::Coord &aCoord) const = 0;
    };
  };
};

#endif //H_BOARD_TRAITS_H
