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
    class Color;

    class PositionAnalyser
    {
    public:
      typedef std::list<Move> MoveList;

    public:
      void setPosition(const Engine::Board &aBoard);
      virtual Engine::Move createMove(const Engine::CoordSequence &aCoorsSequence, bool aUpdateColorIfNeeded = true) = 0;
      Engine::Move createMove(const Engine::CoordSequence &aCoorsSequence, const Engine::Board &aBoard, bool aUpdateColorIfNeeded = true);

      virtual void setPosition(const Engine::Board &aBoard, const Engine::Color &aColor) = 0;
      virtual const MoveList &validMoves() = 0;
      const MoveList &validMoves(const Engine::Board &aBoard, const Engine::Color &aColor);
    };
  };
};

#endif //H_POSITION_ANALYSER_H
