#ifndef H_AMERICAN_CHECKERS_ACTION_FACTORY_H
#define H_AMERICAN_CHECKERS_ACTION_FACTORY_H

#include "ActionAtBoard.h"


namespace Checkers
{
  namespace Engine
  {
    class Board;
    class Move;
    class Coord;
    class ActionTake;

    class AmericanCheckersActionFactory
    {
    private:
      typedef ActionAtBoard::Ptr (AmericanCheckersActionFactory::*ActionFactoryMethod)(const Board &aBoard, const Move &aMove) const;

      class Error
      {
      };

    public:
      ActionAtBoard::Ptr createAction(const Board &aBoard, const Move &aMove) const;

    private:
      ActionAtBoard::Ptr whileNotCreated(const ActionFactoryMethod *aFactoryMethods, const Board &aBoard, const Move &aMove) const;

      ActionAtBoard::Ptr noRequestedDraught(const Board &aBoard, const Move &aMove) const;
      ActionAtBoard::Ptr toBusySquare(const Board &aBoard, const Move &aMove) const;
      ActionAtBoard::Ptr overBusySquare(const Board &aBoard, const Move &aMove) const;

      ActionAtBoard::Ptr simpleMove(const Board &aBoard, const Move &aMove) const;
      ActionAtBoard::Ptr jump(const Board &aBoard, const Move &aMove) const;

      ActionAtBoard::Ptr doJumpStep(Board &aBoard, const Coord &from, const Coord &to, ActionTake &aTake, bool aIsLast) const;
    };
  }
}

#endif //H_AMERICAN_CHECKERS_ACTION_FACTORY_H
