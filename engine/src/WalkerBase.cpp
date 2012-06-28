#include "WalkerBase.h"
#include "Iteration.h"

using namespace Checkers::Engine;


Loop::WalkerBase::WalkerBase()
  : m_ready_to_go(false)
  , m_registered(false)
  , m_waiting_for_removal(false)
{
}

bool Loop::WalkerBase::isReadyToGo() const
{
  return m_ready_to_go;
}

void Loop::WalkerBase::readyToGo()
{
  m_ready_to_go = true;
}

void Loop::WalkerBase::sleep()
{
  m_ready_to_go = false;
}

void Loop::WalkerBase::registerForNextIteration(Loop::WalkerBase::Ptr aPtr, bool aSetReadyToGo)
{
  if(!m_registered)
  {
    Loop::Iteration::instance().registerForNextIteration(aPtr);
    m_registered = true;
  }

  if(aSetReadyToGo)
    readyToGo();
}

void Loop::WalkerBase::removeFromIteration()
{
  m_waiting_for_removal = true;
}

bool Loop::WalkerBase::isWaitingForRemoval() const
{
  return m_waiting_for_removal;
}

void Loop::WalkerBase::removed()
{
  m_waiting_for_removal = false;
  m_registered = false;
}
