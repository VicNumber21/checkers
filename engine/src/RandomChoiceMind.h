#ifndef H_RANDOM_CHOICE_MIND_H
#define H_RANDOM_CHOICE_MIND_H

#include "Walker.h"
#include "PlayerMind.h"


namespace Checkers
{
  namespace Engine
  {
    class RandomChoiceMind : public Loop::Walker<RandomChoiceMind>
                           , public PlayerMind
    {
    public:
      typedef Loop::Walker<RandomChoiceMind>::Ptr Ptr;

      class Error : public Engine::Error
      {
      };

    public:
      static RandomChoiceMind::Ptr create();

    private:
      RandomChoiceMind();

      virtual void thinkOfMove(MoveReceiver::Ptr aPtr);
      virtual void doStep();

    private:
      MoveReceiver::Ptr m_move_receiver;
    };
  };
};

#endif //H_RANDOM_CHOICE_MIND_H
