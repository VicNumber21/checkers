#include "AmericanCheckersActionFactory.h"
#include "Move.h"
#include "Board.h"
#include "ActionThrowError.h"

using namespace Checkers::Engine;


ActionAtBoard::Ptr AmericanCheckersActionFactory::createAction(const Board &aBoard, const Move &aMove) const
{
  ActionFactoryMethod factories[] = 
        {
          &AmericanCheckersActionFactory::noRequestedDraught
        , &AmericanCheckersActionFactory::toBusySquare
        , &AmericanCheckersActionFactory::overBusySquare
        , 0
        };
  return whileNotCreated(factories, aBoard, aMove);
}

ActionAtBoard::Ptr AmericanCheckersActionFactory::whileNotCreated(const ActionFactoryMethod *aFactoryMethods, const Board &aBoard, const Move &aMove) const
{
  ActionAtBoard::Ptr ret;

  int i = 0;
  for(ActionFactoryMethod f = aFactoryMethods[i]; ret == 0 && f != 0; f = aFactoryMethods[++i])
  {
    ret = (this->*f)(aBoard, aMove);
  }

  return ret;
}

ActionAtBoard::Ptr AmericanCheckersActionFactory::noRequestedDraught(const Board &aBoard, const Move &aMove) const
{
  Maybe<Draught> test = aBoard.testSquare(*aMove.begin());

  ActionAtBoard::Ptr ret;

  if(test.isNothing())
  {
    ret.reset(new ActionThrowError<Move::ErrorNoRequestedDraught>);
  }

  return ret;
}

ActionAtBoard::Ptr AmericanCheckersActionFactory::toBusySquare(const Board &aBoard, const Move &aMove) const
{
  ActionAtBoard::Ptr ret;

  Maybe<Draught> testTo = aBoard.testSquare(*(--aMove.end()));
  if(!testTo.isNothing())
  {
    ret.reset(new ActionThrowError<Move::ErrorToBusySquare>);
  }

  return ret;
}

ActionAtBoard::Ptr AmericanCheckersActionFactory::overBusySquare(const Board &aBoard, const Move &aMove) const
{
  ActionAtBoard::Ptr ret;

  int score = aMove.score() - 1;
  for(Move::Iterator it = ++aMove.begin(); score > 0; --score, ++it)
  {
    Maybe<Draught> testOver = aBoard.testSquare(*it);
    if(!testOver.isNothing())
    {
      ret.reset(new ActionThrowError<Move::ErrorJumpOverBusySquare>);
      break;
    }
  }

  return ret;
}
