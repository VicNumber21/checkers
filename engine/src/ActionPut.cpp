#include "ActionPut.h"
#include "Draught.h"
#include "Board.h"

using namespace Checkers::Engine;


ActionPut::ActionPut()
{
}

ActionPut::ActionPut(const ActionPut &anAction)
  : m_draught_list(anAction.m_draught_list)
{
}

void ActionPut::append(const Engine::Draught &aDraught)
{
  m_draught_list.push_back(aDraught);
}

void ActionPut::perform(Board &aBoard) const
{
  for(Iterator it = m_draught_list.begin(); it != m_draught_list.end(); ++it)
  {
    if(!aBoard.put(*it))
    {
      throw ActionPut::ErrorToBusySquare();
    }
  }
}
