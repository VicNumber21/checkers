#ifndef H_MOVE_H
#define H_MOVE_H

#include "Coord.h"
#include "Board.h"

#include <list>


namespace Checkers
{
  namespace Engine
  {
    class Move
    {
    public:
      typedef std::list<Engine::Coord> CoordList;
      typedef CoordList::const_iterator Iterator;

      class ErrorNoRequestedDraught
      {
      };

      class ErrorNothingToJumpOver
      {
      };

      class ErrorInWrongDirection
      {
      };

      class ErrorToBusySquare
      {
      };

      class ErrorJumpOverBusySquare
      {
      };

      class ErrorJumpExist
      {
      };

      class ErrorJumpOverSameColor
      {
      };

      class ErrorGetKingButMoveFurther
      {
      };

      class ErrorUnexpectedAppend
      {
      };

      class ErrorUndefinedUsage
      {
      };

      class ErrorCoordSequence
      {
      public:
        ErrorCoordSequence(const Move::CoordList &aCoordList);

      public:
        Move::CoordList m_coord_list;
      };

      enum Type
      {
        EUndefined
      , ESimple
      , EJump
      };

    public:
      Move();
      Move(const Engine::Coord &aStart, const Engine::Coord &aNext, Type aType = ESimple);
      Move(const Engine::Move &aMove);

      void append(const Engine::Coord &aNext);

      int score() const;
      Type type() const;

      Move & operator=(const Engine::Move &aMove);

      bool operator==(const Engine::Move &aMove) const;
      bool operator!=(const Engine::Move &aMove) const;

      Move::Iterator begin() const;
      Move::Iterator end() const;

    private:
      void validateTail() const;
      void throwIfUndefined() const;
      bool isJumpBack(Iterator aLast, Iterator aThirdFromTail) const;

    private:
      CoordList m_coord_list;
      Type m_type;
    };

    Board operator+(const Board &aCurrent, const Move &aMove);
    // TODO remove if not needed -> Board operator-(const Board &aNext, const Move &aMove);
    Move operator-(const Board &aNext, const Board &aCurrent);
  };
};

#endif //H_MOVE_H
