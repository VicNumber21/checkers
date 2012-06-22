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

      class BoardBounds
      {
      public:
        static int height();
        static int width();

        static char rowName(int aN);
        static char columnName(int aM);

        static int rowIndex(char aY);
        static int columnIndex(char aX);

        static bool isColumnInBound(int aX);
        static bool isColumnInBound(char aX);

        static bool isRowInBound(int aY);
        static bool isRowInBound(char aY);

        static bool isKingRow(int aY, const Engine::Color &aColor);
        static bool isKingRow(char aY, const Engine::Color &aColor);
      };

      class MoveValidator
      {
      public:
        static bool isValidCoord(const Engine::Coord &aCoord);

        static bool isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond);
        static bool isValidCoordSequence(const Engine::Coord &aFirst, const Engine::Coord &aSecond, const Engine::Coord &aThird);
        static bool isValidDirection(const Engine::Coord &aFirst, const Engine::Coord &aSecond
                                     , const Engine::Color &aColor, bool isKing);

        static PositionAnalyser & positionAnalyser();
      };
    };
  };
};

#endif //H_RULES_OF_GAME_H
