#ifndef H_ACTION_SEQUENCE_H
#define H_ACTION_SEQUENCE_H

#include "ActionAtBoard.h"
#include <list>


namespace Checkers
{
  namespace Engine
  {
    class ActionSequence : public ActionAtBoard
    {
    public:
      typedef std::list<Engine::ActionAtBoard::Ptr> ActionList;
      typedef ActionList::const_iterator Iterator;

    public:
      ActionSequence();
      ActionSequence(const ActionSequence &anAction);
      void append(const Engine::ActionAtBoard::Ptr aActionPtr);

      virtual void perform(Board &aBoard) const;

    private:
      ActionList m_action_list;
    };
  }
}

#endif //H_ACTION_SEQUENCE_H
