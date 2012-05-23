#ifndef H_ACTION_PUT_H
#define H_ACTION_PUT_H

#include "ActionAtBoard.h"
#include <list>


namespace Checkers
{
  namespace Engine
  {
    class Draught;

    class ActionPut : public ActionAtBoard
    {
    public:
      typedef std::list<Engine::Draught> DraughtList;
      typedef DraughtList::const_iterator Iterator;

      class ErrorToBusySquare
      {
      };

    public:
      ActionPut();
      ActionPut(const ActionPut &anAction);
      void append(const Engine::Draught &aDraught);

      virtual void perform(Board &aBoard) const;

    private:
      DraughtList m_draught_list;
    };
  }
}

#endif //H_ACTION_PUT_H
