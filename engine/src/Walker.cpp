#include "Walker.h"
#include "Iteration.h"

using namespace Checkers::Engine;


Loop::Walker::Walker()
  : m_ready_to_go(false)
  , m_registered(false)
  , m_waiting_for_removal(false)
{
}

void Loop::Walker::setSelf(const Walker::Ptr &aSelf)
{
  m_self = aSelf;
}

bool Loop::Walker::isReadyToGo() const
{
  return m_ready_to_go;
}

void Loop::Walker::readyToGo()
{
  m_ready_to_go = true;
}

void Loop::Walker::sleep()
{
  m_ready_to_go = false;
}

void Loop::Walker::registerForNextIteration(bool aSetReadyToGo)
{
  if(m_self.expired())
    throw Walker::Error();

  if(!m_registered)
  {
    Loop::Iteration::instance().registerForNextIteration(m_self.lock());
    m_registered = true;
  }

  if(aSetReadyToGo)
    readyToGo();
}

void Loop::Walker::removeFromIteration()
{
  m_waiting_for_removal = true; 
}

bool Loop::Walker::isWaitingForRemoval() const
{
  return m_waiting_for_removal;
}

void Loop::Walker::removed()
{
  m_waiting_for_removal = false;
  m_registered = false;
}
