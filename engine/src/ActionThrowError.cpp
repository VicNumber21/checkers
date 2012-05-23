#include "ActionThrowError.h"
#include "Move.h"

using namespace Checkers::Engine;


template <class E>
void ActionThrowError<E>::perform(Board &aBoard) const
{
  (void) aBoard;

  throw E();
}

template class ActionThrowError<Move::ErrorNoRequestedDraught>;
template class ActionThrowError<Move::ErrorToBusySquare>;
template class ActionThrowError<Move::ErrorJumpOverBusySquare>;
template class ActionThrowError<Move::ErrorInWrongDirection>;
template class ActionThrowError<Move::ErrorJumpExist>;
