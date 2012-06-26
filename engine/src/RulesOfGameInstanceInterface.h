#ifndef H_RULES_OF_GAME_INSTANCE_INTERFACE_H
#define H_RULES_OF_GAME_INSTANCE_INTERFACE_H

#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    class PositionAnalyser;
    class BoardTraits;

    class RulesOfGameInstanceInterface
    {
    public:
      typedef std::tr1::shared_ptr<Engine::RulesOfGameInstanceInterface> Ptr;

    public:
      virtual void activate() = 0;
      virtual void deactivate() = 0;

      virtual const Engine::BoardTraits &boardTraits() const = 0;
      virtual Engine::PositionAnalyser &positionAnalyser() = 0;
    };
  };
};

#endif //H_RULES_OF_GAME_INSTANCE_INTERFACE_H
