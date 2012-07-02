#ifndef H_GAME_MANAGER_H
#define H_GAME_MANAGER_H

#include "Board.h"
#include "Error.h"


namespace Checkers
{
  namespace Engine
  {
    class Move;

    class GameManager
    {
    public:
      class Error : public Engine::Error
      {
      };

    public:
      static GameManager &instance();

      void setCurrentBoard(const Board &aBoard = Board());
      const Board &currentBoard() const;

      void applyMove(const Move &aMove);

    private:
      GameManager();
      Board initialBoard() const; //TODO shall be in RulesOfGame

    private:
      Board m_current_board;
    };
  };
};

#endif //H_GAME_MANAGER_H
