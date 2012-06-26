#ifndef H_RULES_OF_GAME_INSTANCES_H
#define H_RULES_OF_GAME_INSTANCES_H

#include "RulesOfGameInstanceInterface.h"
#include "Error.h"

#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    class RulesOfGameInstanceError : public Engine::Error
    {
    };

    template <class BOARD_TRAITS, class POSITION_ANALYSER>
    class RulesOfGameInstanceTemplate : public RulesOfGameInstanceInterface
    {
    public:
      virtual void activate();
      virtual void deactivate();

      virtual const Engine::BoardTraits &boardTraits() const;
      virtual Engine::PositionAnalyser &positionAnalyser();

    private:
      template <class _BOARD_TRAITS, class _POSITION_ANALYSER>
      struct _RulesOfGameObjects
      {
        _BOARD_TRAITS m_board_traits;
        _POSITION_ANALYSER m_position_analyser;
      };

      typedef _RulesOfGameObjects<BOARD_TRAITS, POSITION_ANALYSER> RulesOfGameObjects;
      typedef std::tr1::shared_ptr<RulesOfGameObjects> RulesOfGameObjectsPtr;

    private:
      void throwIfNotActive() const;

    private:
      RulesOfGameObjectsPtr m_objects;
    };

    class AmericanCheckersBoardTraits;
    class AmericanCheckersPositionAnalyser;
    typedef RulesOfGameInstanceTemplate<AmericanCheckersBoardTraits, AmericanCheckersPositionAnalyser> AmericanCheckersRulesOfGame;
  };
};

#endif //H_RULES_OF_GAME_INSTANCES_H
