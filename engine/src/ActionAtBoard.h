#ifndef H_ACTION_AT_BOARD_H
#define H_ACTION_AT_BOARD_H

#include <list>
#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    class Board;

    class ActionAtBoard
    {
    public:
      typedef std::tr1::shared_ptr<ActionAtBoard> Ptr;

    public:
      virtual ~ActionAtBoard();
      virtual void perform(Board &aBoard) const = 0;
    };

    typedef std::list<ActionAtBoard::Ptr> ActionsAtBoard;
  }
}

#endif //H_ACTION_AT_BOARD_H
