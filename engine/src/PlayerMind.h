#ifndef H_PLAYER_MIND_H
#define H_PLAYER_MIND_H

#include "MoveReceiver.h"

#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    class PlayerMind
    {
    public:
      typedef std::tr1::weak_ptr<PlayerMind> Ptr;

    public:
      virtual void thinkOfMove(Engine::MoveReceiver::Ptr aPtr) = 0;
    };
  };
};

#endif //H_PLAYER_MIND_H
