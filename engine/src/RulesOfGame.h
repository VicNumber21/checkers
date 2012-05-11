#ifndef H_RULES_OF_GAME_H
#define H_RULES_OF_GAME_H

#include "ActionAtBoard.h"


namespace Checkers
{
  namespace Engine
  {
    class Move;
    class Coord;
    class Board;

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
        static Engine::ActionAtBoard::Ptr transformIntoActions(const Engine::Board &aBoard, const Engine::Move &aMove);

      private:
        static void initPrototypes();
        static const ActionsAtBoard & actionPrototypes();

      private:
        static ActionsAtBoard m_action_prototypes;
      };
    };
  };
};

#endif //H_RULES_OF_GAME_H
