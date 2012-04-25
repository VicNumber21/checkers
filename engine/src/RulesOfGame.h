#ifndef H_RULES_OF_GAME_H
#define H_RULES_OF_GAME_H


namespace Checkers
{
  namespace Engine
  {
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
    };
  };
};

#endif //H_RULES_OF_GAME_H
