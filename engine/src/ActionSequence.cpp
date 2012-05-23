#include "ActionSequence.h"

using namespace Checkers::Engine;


ActionSequence::ActionSequence()
{
}

ActionSequence::ActionSequence(const ActionSequence &anAction)
  : m_action_list(anAction.m_action_list)
{
}

void ActionSequence::append(const Engine::ActionAtBoard::Ptr aActionPtr)
{
  m_action_list.push_back(aActionPtr);
}

void ActionSequence::perform(Board &aBoard) const
{
  for(Iterator it = m_action_list.begin(); it != m_action_list.end(); ++it)
  {
    (*it)->perform(aBoard);
  }
}
