#ifndef H_RULES_OF_GAME_H
#define H_RULES_OF_GAME_H


namespace Checkers
{
  namespace Engine
  {
    class Move;
    class Coord;

    class RulesOfGame
    {
    public:
      class BoardBounds
      {
      public:
        static int height();
        static int width();

        static char lineName(int aN);
        static char columnName(int aM);

        static int lineIndex(char aY);
        static int columnIndex(char aX);

        static bool isColumnInBound(int aX);
        static bool isColumnInBound(char aX);

        static bool isLineInBound(int aY);
        static bool isLineInBound(char aY);
      };

      class MoveValidator
      {
      public:
        static bool isValidCoord(const Engine::Coord &aCoord);
        static bool isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, bool isJump);
      };
    };
  };
};

#endif //H_RULES_OF_GAME_H
