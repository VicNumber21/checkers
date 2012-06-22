#ifndef H_AMERICAN_CHECKERS_BOARD_TRAITS_H
#define H_AMERICAN_CHECKERS_BOARD_TRAITS_H

#include "BoardTraits.h"


namespace Checkers
{
  namespace Engine
  {
    class AmericanCheckersBoardTraits : public BoardTraits
    {
    public:
      virtual int height() const;
      virtual int width() const;

      virtual char rowName(int aN) const;
      virtual char columnName(int aM) const;

      virtual int rowIndex(char aY) const;
      virtual int columnIndex(char aX) const;

      virtual bool isColumnInBound(int aX) const;
      virtual bool isColumnInBound(char aX) const;

      virtual bool isRowInBound(int aY) const;
      virtual bool isRowInBound(char aY) const;

      virtual bool canPutManOnKingRow() const;

      virtual bool isKingRow(int aY, const Engine::Color &aColor) const;
      virtual bool isKingRow(char aY, const Engine::Color &aColor) const;

      virtual bool isBlackSquare(const Engine::Coord &aCoord) const;
      virtual bool isWhiteSquare(const Engine::Coord &aCoord) const;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_BOARD_TRAITS_H
