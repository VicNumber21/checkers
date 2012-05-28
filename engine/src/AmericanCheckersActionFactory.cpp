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
        , &AmericanCheckersActionFactory::jump
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

  Coord from(*aMove.begin());
  Coord to(*(--aMove.end()));

  if(to != from)
  {
    Maybe<Draught> testTo = aBoard.testSquare(to);
    if(!testTo.isNothing())
    {
      ret.reset(new ActionThrowError<Move::ErrorToBusySquare>);
    }
  }

  return ret;
}

ActionAtBoard::Ptr AmericanCheckersActionFactory::overBusySquare(const Board &aBoard, const Move &aMove) const
{
  ActionAtBoard::Ptr ret;

  int score = aMove.score() - 1;
  Coord from(*aMove.begin());
  for(Move::Iterator it = ++aMove.begin(); score > 0; --score, ++it)
  {
    if(from == *it)
      continue;

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

ActionAtBoard::Ptr AmericanCheckersActionFactory::jump(const Board &aBoard, const Move &aMove) const
{
  ActionAtBoard::Ptr ret;

  if(aMove.score() > 0)
  {
    Board testBoard(aBoard);

    ActionTake *takeA = new ActionTake;
    ActionAtBoard::Ptr takeAPtr(takeA);
    takeA->append(*aMove.begin());

    ActionAtBoard::Ptr error;
    Move::Iterator lastIt = --aMove.end();

    for(Move::Iterator toIt = ++aMove.begin(); !error && toIt != aMove.end(); ++toIt)
    {
      Move::Iterator fromIt = toIt;
      --fromIt;

      error = doJumpStep(testBoard, *fromIt, *toIt, *takeA, toIt == lastIt);
    }

    if(error)
    {
      ret = error;
    }
    else
    {
      Coord to(*(--aMove.end()));

      ActionPut *putA = new ActionPut;
      ActionAtBoard::Ptr putAPtr(putA);
      putA->append(testBoard.testSquare(to)());

      ActionSequence *sequenceA = new ActionSequence;
      ActionAtBoard::Ptr sequenceAPtr(sequenceA);
      sequenceA->append(takeAPtr);
      sequenceA->append(putAPtr);

      ret = sequenceAPtr;
    }
  }

  return ret;
}

ActionAtBoard::Ptr AmericanCheckersActionFactory::doJumpStep(Board &aBoard, const Coord &from, const Coord &to, ActionTake &aTake, bool aIsLast) const
{
  ActionAtBoard::Ptr ret;

  Draught draught = aBoard.takeDraught(from)();
  int deltaX = to.x() - from.x() > 0 ? 1 : -1;
  int deltaY = to.y() - from.y() > 0 ? 1 : -1;
  Coord between(from.x() + deltaX, from.y() + deltaY);
  Maybe<Draught> maybeJumped = aBoard.takeDraught(between);

  if(!maybeJumped.isNothing())
  {
    if(maybeJumped().color() != draught.color())
    {
      if(RulesOfGame::MoveValidator::isValidDirection(from, to, draught.color(), draught.isKing()))
      {
        aTake.append(between);

        draught.moveTo(to);
        bool makeKing = !draught.isKing() && RulesOfGame::BoardBounds::isKingLine(to.y(), draught.color());
        if(makeKing)
        {
          draught.makeKing();
        }
        if(!aBoard.put(draught))
        {
          throw AmericanCheckersActionFactory::Error();
        }

        if(makeKing && !aIsLast)
        {
          ret.reset(new ActionThrowError<Move::ErrorGetKingButMoveFurther>);
        }
        else if(!makeKing && aIsLast && RulesOfGame::MoveValidator::doesJumpExist(aBoard, draught))
        {
          ret.reset(new ActionThrowError<Move::ErrorJumpExist>);
        }
      }
      else
      {
        ret.reset(new ActionThrowError<Move::ErrorInWrongDirection>);
      }
    }
    else
    {
      ret.reset(new ActionThrowError<Move::ErrorJumpOverSameColor>);
    }
  }
  else
  {
    ret.reset(new ActionThrowError<Move::ErrorNothingToJumpOver>);
  }

  return ret;
}
