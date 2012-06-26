#ifndef H_RULES_OF_GAME_MANAGER_H
#define H_RULES_OF_GAME_MANAGER_H

#include "RulesOfGameInstanceInterface.h"
#include "Error.h"

#include <vector>


namespace Checkers
{
  namespace Engine
  {
    class PositionAnalyser;
    class BoardTraits;

    class RulesOfGameManager
    {
    public:
      class Error : public Engine::Error
      {
      };

    public:
      static RulesOfGameManager &instance();

      int append(Engine::RulesOfGameInstanceInterface::Ptr aInstance, bool aSetAsCurrent = false);
      void reset();

      int getCurrentRulesOfGameId() const;
      bool setCurrentRulesOfGame(int aId);

      const Engine::BoardTraits &currentBoardTraits() const;
      Engine::PositionAnalyser &currentPositionAnalyser();

    private:
      typedef std::vector<RulesOfGameInstanceInterface::Ptr> InstanceStorage;

    private:
      RulesOfGameManager();

      RulesOfGameInstanceInterface::Ptr &currentInstance();
      const RulesOfGameInstanceInterface::Ptr &currentInstance() const;
      void throwIfCannotGetCurrentInstance() const;

    private:
      InstanceStorage m_instances;
      int m_current_id;
    };
  };
};

#endif //H_RULES_OF_GAME_MANAGER_H
