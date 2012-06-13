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

        static bool isKingLine(int aY, const Engine::Color &aColor);
        static bool isKingLine(char aY, const Engine::Color &aColor);
      };

      class MoveValidator
      {
      public:
        static bool isValidCoord(const Engine::Coord &aCoord);

        static bool isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond);
        static bool isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, const Engine::Coord &aThird);
        static bool isValidDirection(const Engine::Coord &aFirst, const Engine::Coord &aSecond
                                     , const Engine::Color &aColor, bool isKing);
        static bool doesJumpExist(const Engine::Board &aBoard, const Engine::Draught &aDraught);
        static bool doesJumpExist(const Engine::Board &aBoard, const Engine::Color &aColor);

        static PositionAnalyser & positionAnalyser();
      };
    };
  };
};

#endif //H_RULES_OF_GAME_H
