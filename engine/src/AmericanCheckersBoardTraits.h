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

      virtual char lineName(int aN) const;
      virtual char columnName(int aM) const;

      virtual int lineIndex(char aY) const;
      virtual int columnIndex(char aX) const;

      virtual bool isColumnInBound(int aX) const;
      virtual bool isColumnInBound(char aX) const;

      virtual bool isLineInBound(int aY) const;
      virtual bool isLineInBound(char aY) const;

      virtual bool isKingLine(int aY, const Engine::Color &aColor) const;
      virtual bool isKingLine(char aY, const Engine::Color &aColor) const;

      virtual bool isBlackSquare(const Engine::Coord &aCoord) const;
      virtual bool isWhiteSquare(const Engine::Coord &aCoord) const;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_BOARD_TRAITS_H
