#include "ActionNoRequestedDraught.h"
#include "Move.h"
#include "Board.h"

using namespace Checkers::Engine;


void ActionNoRequestedDraught::perform(Board &aBoard) const
{
  (void) aBoard;

  throw Move::ErrorNoRequestedDraught();
}

ActionAtBoard::Ptr ActionNoRequestedDraught::cloneIfNeeded(const Board &aBoard, const Move &aMove) const
{
  Maybe<Draught> test = aBoard.testSquare(*aMove.begin());

  ActionNoRequestedDraught::Ptr ret;

  if(test.isNothing())
  {
    ret.reset(new ActionNoRequestedDraught);
  }

  return ret;
}
