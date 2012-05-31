#ifndef H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
#define H_AMERICAN_CHECKERS_POSITION_ANALYSER_H

#include "PositionAnalyser.h"
#include "Board.h"


namespace Checkers
{
  namespace Engine
  {
    class AmericanCheckersPositionAnalyser: public PositionAnalyser
    {
    public:
      AmericanCheckersPositionAnalyser();

      virtual void setPosition(const Engine::Board &aBoard);

      virtual Engine::Move createMove(const Engine::CoordSequence &aCoorsSequence) const;

      virtual MoveList validMoves() const;

    private:
      Board m_current_board;
      MoveList m_valid_simple_moves;
      MoveList m_valid_jumps;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
