#include "Iteration.h"

using namespace Checkers::Engine;


Loop::Iteration & Loop::Iteration::instance()
{
  static Loop::Iteration iteration;
  return iteration;
}

Loop::Iteration::Iteration()
{
}

void Loop::Iteration::registerForNextIteration(const Loop::Walker::Ptr &aWalker)
{
  m_walkers.push_front(aWalker);
}

void Loop::Iteration::removeAll(bool aNow)
{
  for(WalkerStorage::iterator it = m_walkers.begin(); it != m_walkers.end();)
  {
    if(aNow)
    {
      it = removeWalker(it);
    }
    else
    {
      (*it)->removeFromIteration();
      ++it;
    }
  }
}

Loop::Iteration::WalkerStorage::iterator Loop::Iteration::removeWalker(Loop::Iteration::WalkerStorage::iterator aWalker)
{
  (*aWalker)->removed();
  return m_walkers.erase(aWalker);
}

void Loop::Iteration::walk()
{
  for(WalkerStorage::iterator it = m_walkers.begin(); it != m_walkers.end();)
  {
    Walker::Ptr currentWalker = *it;

    if(currentWalker->isWaitingForRemoval())
    {
      it = removeWalker(it);
    }
    else 
    {
      if(currentWalker->isReadyToGo())
      {
        currentWalker->doStep();

        if(isEmpty()) //it makes removeAll(true) safe from doStep()
          break;
      }

      ++it;
    }
  }
}

bool Loop::Iteration::isEmpty() const
{
  return m_walkers.size() == 0;
}
