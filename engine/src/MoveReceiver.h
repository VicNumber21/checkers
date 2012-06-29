#ifndef H_MOVE_RECEIVER_H
#define H_MOVE_RECEIVER_H

#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    class CoordSequence;
    class Move;

    class MoveReceiver
    {
    public:
      typedef std::tr1::weak_ptr<MoveReceiver> Ptr;

    public:
      virtual void set(const Engine::CoordSequence &aCoordSequence) = 0;
      virtual void set(const Engine::Move &aMove) = 0;
    };
  };
};

#endif //H_MOVE_RECEIVER_H
