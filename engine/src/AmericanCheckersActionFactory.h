#ifndef H_AMERICAN_CHECKERS_ACTION_FACTORY_H
#define H_AMERICAN_CHECKERS_ACTION_FACTORY_H

#include "ActionAtBoard.h"


namespace Checkers
{
  namespace Engine
  {
    class Board;
    class Move;

    class AmericanCheckersActionFactory
    {
    private:
      typedef ActionAtBoard::Ptr (AmericanCheckersActionFactory::*ActionFactoryMethod)(const Board &aBoard, const Move &aMove) const;

    public:
      ActionAtBoard::Ptr createAction(const Board &aBoard, const Move &aMove) const;

    private:
      ActionAtBoard::Ptr whileNotCreated(const ActionFactoryMethod *aFactoryMethods, const Board &aBoard, const Move &aMove) const;

      ActionAtBoard::Ptr noRequestedDraught(const Board &aBoard, const Move &aMove) const;
      ActionAtBoard::Ptr toBusySquare(const Board &aBoard, const Move &aMove) const;
      ActionAtBoard::Ptr overBusySquare(const Board &aBoard, const Move &aMove) const;

      ActionAtBoard::Ptr simpleMove(const Board &aBoard, const Move &aMove) const;
    };
  }
}

#endif //H_AMERICAN_CHECKERS_ACTION_FACTORY_H
