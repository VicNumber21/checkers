#ifndef H_ACTION_TAKE_H
#define H_ACTION_TAKE_H

#include "ActionAtBoard.h"
#include <list>


namespace Checkers
{
  namespace Engine
  {
    class Coord;

    class ActionTake : public ActionAtBoard
    {
    public:
      typedef std::list<Engine::Coord> CoordList;
      typedef CoordList::const_iterator Iterator;

      class ErrorNothingToTake
      {
      };

    public:
      ActionTake();
      ActionTake(const ActionTake &anAction);
      void append(const Engine::Coord &aCoord);

      virtual void perform(Board &aBoard) const;

    private:
      CoordList m_coord_list;
    };
  }
}

#endif //H_ACTION_TAKE_H
