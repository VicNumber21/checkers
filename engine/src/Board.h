#ifndef H_BOARD_H
#define H_BOARD_H

#include "Draught.h"
#include "Maybe.h"

#include <set>


namespace Checkers
{
  namespace Engine
  {
    class Coord;
    class Draught;

    class Board
    {
    private:
      typedef std::set<Engine::Draught> DraughtSet;
      typedef DraughtSet::iterator iterator;

    public:
      typedef DraughtSet::const_iterator Iterator;

      enum Ord
      {
        ELess = -1
      , EEqual = 0
      , EBigger = 1
      };

    public:
      Board();
      Board(const Engine::Board &aBoard);

      bool put(const Engine::Draught &aDraught);
      Maybe<Engine::Draught> takeDraught(const Engine::Coord &aCoord);
      Maybe<Engine::Draught> testSquare(const Engine::Coord &aCoord) const;

      int count() const;
      int count(const Engine::Color aColor) const;

      Board & operator=(const Engine::Board &aBoard);

      Ord compare(const Engine::Board &aBoard) const;
      bool operator==(const Engine::Board &aBoard) const;
      bool operator!=(const Engine::Board &aBoard) const;
      bool operator<(const Engine::Board &aBoard) const;
      bool operator>(const Engine::Board &aBoard) const;

      Board::Iterator begin() const;
      Board::Iterator end() const;

    private:
      Maybe<Engine::Draught> getDraught(const Engine::Coord &aCoord, bool aKeepOnBoard) const;

    private:
      DraughtSet m_draught_set;
    };
  };
};

#endif //H_BOARD_H
