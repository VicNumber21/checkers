#ifndef H_POSITION_ANALYSER_H
#define H_POSITION_ANALYSER_H

#include "Move.h"

#include <set>


namespace Checkers
{
  namespace Engine
  {
    class CoordSequence;
    class Board;
    class Color;

    class PositionAnalyser
    {
    public:
      //TODO: Move it out?
      class LessTo : public std::binary_function<Engine::Move, Engine::Move, bool>
      {
      public:
        bool operator()(const Engine::Move &aFirst, const Engine::Move &aSecond) const
        {
          return aFirst.to() < aSecond.to();
        }
      };

      typedef std::set<Move, LessTo> MoveList;

      class ErrorNotFound : public Engine::Error
      {
      };

    public:
      void setPosition(const Engine::Board &aBoard);
      virtual Engine::Move createMove(const Engine::CoordSequence &aCoordSequence, bool aUpdateColorIfNeeded = true) = 0;
      Engine::Move createMove(const Engine::CoordSequence &aCoordSequence, const Engine::Board &aBoard, bool aUpdateColorIfNeeded = true);

      virtual Engine::CoordSequence createCoordSequence(const Engine::Move &aMove) = 0;

      virtual void setPosition(const Engine::Board &aBoard, const Engine::Color &aColor) = 0;
      virtual const MoveList &validMoves() const = 0;
      const MoveList &validMoves(const Engine::Board &aBoard, const Engine::Color &aColor);
    };
  };
};

#endif //H_POSITION_ANALYSER_H
