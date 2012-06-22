#ifndef H_RULES_OF_GAME_H
#define H_RULES_OF_GAME_H


namespace Checkers
{
  namespace Engine
  {
    class CoordSequence;
    class Coord;
    class Board;
    class Color;
    class Draught;
    class PositionAnalyser;
    class BoardTraits;

    class RulesOfGame
    {
    public:
        static const BoardTraits &boardTraits();
        static PositionAnalyser &positionAnalyser();
    };
  };
};

#endif //H_RULES_OF_GAME_H
