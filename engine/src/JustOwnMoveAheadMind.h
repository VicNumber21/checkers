#ifndef H_JUST_OWN_MOVE_AHEAD_MIND_H
#define H_JUST_OWN_MOVE_AHEAD_MIND_H

#include "Walker.h"
#include "PlayerMind.h"


namespace Checkers
{
  namespace Engine
  {
    class JustOwnMoveAheadMind : public Loop::Walker<JustOwnMoveAheadMind>
                               , public PlayerMind
    {
    public:
      typedef Checkers::Engine::Loop::Walker<JustOwnMoveAheadMind>::Ptr Ptr;

      class Error : public Engine::Error
      {
      };

    public:
      static JustOwnMoveAheadMind::Ptr create();

    private:
      JustOwnMoveAheadMind();

      virtual void thinkOfMove(MoveReceiver::Ptr aPtr);
      virtual void doStep();

    private:
      MoveReceiver::Ptr m_move_receiver;
    };
  };
};

#endif //H_JUST_OWN_MOVE_AHEAD_MIND_H
