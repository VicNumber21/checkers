#include "ActionTake.h"
#include "Coord.h"
#include "Board.h"

using namespace Checkers::Engine;


ActionTake::ActionTake()
{
}

ActionTake::ActionTake(const ActionTake &anAction)
  : m_coord_list(anAction.m_coord_list)
{
}

void ActionTake::append(const Engine::Coord &aCoord)
{
  m_coord_list.push_back(aCoord);
}

void ActionTake::perform(Board &aBoard) const
{
  for(Iterator it = m_coord_list.begin(); it != m_coord_list.end(); ++it)
  {
    if(aBoard.takeDraught(*it).isNothing())
    {
      throw ActionTake::ErrorNothingToTake();
    }
  }
}
