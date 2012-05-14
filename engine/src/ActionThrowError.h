#ifndef H_ACTION_THROW_ERROR_H
#define H_ACTION_THROW_ERROR_H

#include "ActionAtBoard.h"


namespace Checkers
{
  namespace Engine
  {
    template <class E>
    class ActionThrowError : public ActionAtBoard
    {
    public:
      virtual void perform(Board &aBoard) const;
    };
  }
}

#endif //H_ACTION_THROW_ERROR_H
