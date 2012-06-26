#include "RulesOfGameManager.h"


using namespace Checkers::Engine;


RulesOfGameManager & RulesOfGameManager::instance()
{
  static RulesOfGameManager manager;
  return manager;
}

int RulesOfGameManager::append(Engine::RulesOfGameInstanceInterface::Ptr aInstance, bool aSetAsCurrent)
{
  m_instances.push_back(aInstance);

  int id = m_instances.size() - 1;

  if(aSetAsCurrent)
    setCurrentRulesOfGame(id);

  return id;
}

void RulesOfGameManager::reset()
{
  m_instances.clear();
  m_current_id = -1;
}

int RulesOfGameManager::getCurrentRulesOfGameId() const
{
  return m_current_id;
}

bool RulesOfGameManager::setCurrentRulesOfGame(int aId)
{
  bool ret = (aId < (int)m_instances.size());

  if(ret && aId != m_current_id)
  {
    if(m_current_id > 0)
      currentInstance()->deactivate();

    m_current_id = aId;
    currentInstance()->activate();
  }

  return ret;
}

const BoardTraits & RulesOfGameManager::currentBoardTraits() const
{
  return currentInstance()->boardTraits();
}

PositionAnalyser & RulesOfGameManager::currentPositionAnalyser()
{
  return currentInstance()->positionAnalyser();
}

RulesOfGameManager::RulesOfGameManager()
  : m_current_id(-1)
{
}

RulesOfGameInstanceInterface::Ptr & RulesOfGameManager::currentInstance()
{
  throwIfCannotGetCurrentInstance();
  return m_instances[m_current_id];
}

const RulesOfGameInstanceInterface::Ptr & RulesOfGameManager::currentInstance() const
{
  throwIfCannotGetCurrentInstance();
  return m_instances[m_current_id];
}

void RulesOfGameManager::throwIfCannotGetCurrentInstance() const
{
  if(m_current_id < 0)
    throw RulesOfGameManager::Error();
}
