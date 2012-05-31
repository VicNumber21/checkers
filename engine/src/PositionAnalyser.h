#ifndef H_POSITION_ANALYSER_H
#define H_POSITION_ANALYSER_H

#include <list>


namespace Checkers
{
  namespace Engine
  {
    class Move;
    class CoordSequence;
    class Board;

    class PositionAnalyser
    {
    public:
      typedef std::list<Move> MoveList;

    public:
      virtual void setPosition(const Engine::Board &aBoard) = 0;

      virtual Engine::Move createMove(const Engine::CoordSequence &aCoorsSequence) const = 0;
      Engine::Move createMove(const Engine::CoordSequence &aCoorsSequence, const Engine::Board &aBoard);

      virtual MoveList validMoves() const = 0;
      MoveList validMoves(const Engine::Board &aBoard);
    };
  };
};

#endif //H_POSITION_ANALYSER_H
