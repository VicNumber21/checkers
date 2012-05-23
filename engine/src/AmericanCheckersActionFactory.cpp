#include "AmericanCheckersActionFactory.h"
#include "Move.h"
#include "Board.h"
#include "Color.h"
#include "ActionThrowError.h"
#include "ActionTake.h"
#include "ActionPut.h"
#include "ActionSequence.h"
#include "RulesOfGame.h"

using namespace Checkers::Engine;


ActionAtBoard::Ptr AmericanCheckersActionFactory::createAction(const Board &aBoard, const Move &aMove) const
{
  ActionFactoryMethod factories[] = 
        {
          &AmericanCheckersActionFactory::noRequestedDraught
        , &AmericanCheckersActionFactory::toBusySquare
        , &AmericanCheckersActionFactory::overBusySquare
        , &AmericanCheckersActionFactory::simpleMove
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

ActionAtBoard::Ptr AmericanCheckersActionFactory::simpleMove(const Board &aBoard, const Move &aMove) const
{
  ActionAtBoard::Ptr ret;

  if(aMove.score() == 0)
  {
    Move::Iterator to = aMove.begin();
    Move::Iterator from = to++;
    Draught draught = aBoard.testSquare(*from)();

    if(RulesOfGame::MoveValidator::doesJumpExist(aBoard, draught.color()))
    {
      ret.reset(new ActionThrowError<Move::ErrorJumpExist>);
    }
    else
    {
      if(RulesOfGame::MoveValidator::isValidDirection(*from, *to, draught.color(), draught.isKing()))
      {
        ActionTake *takeA = new ActionTake;
        ActionAtBoard::Ptr takeAPtr(takeA);
        takeA->append(*from);

        ActionPut *putA = new ActionPut;
        ActionAtBoard::Ptr putAPtr(putA);
        draught.moveTo(*to);
        if(RulesOfGame::BoardBounds::isKingLine(to->y(), draught.color()))
        {
          draught.makeKing();
        }
        putA->append(draught);

        ActionSequence *sequenceA = new ActionSequence;
        ret.reset(sequenceA);
        sequenceA->append(takeAPtr);
        sequenceA->append(putAPtr);
      }
      else
      {
        ret.reset(new ActionThrowError<Move::ErrorInWrongDirection>);
      }
    }
  }

  return ret;
}
