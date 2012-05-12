#ifndef H_ACTION_NO_REQUESTED_DRAUGHT_H
#define H_ACTION_NO_REQUESTED_DRAUGHT_H

#include "ActionAtBoard.h"


namespace Checkers
{
  namespace Engine
  {
    class ActionNoRequestedDraught : public ActionAtBoard
    {
    public:
      virtual void perform(Board &aBoard) const;
      virtual ActionAtBoard::Ptr cloneIfNeeded(const Board &aBoard, const Move &aMove) const;
    };
  }
}

#endif //H_ACTION_NO_REQUESTED_DRAUGHT_H
