#ifndef H_RANDOM_CHOICE_MIND_H
#define H_RANDOM_CHOICE_MIND_H

#include "Walker.h"
#include "PlayerMind.h"


class RandomChoiceMind : public Checkers::Engine::Loop::Walker<RandomChoiceMind>
                       , public Checkers::Engine::PlayerMind
{
public:
  typedef Checkers::Engine::Loop::Walker<RandomChoiceMind>::Ptr Ptr;

  class Error : public Checkers::Engine::Error
  {
  };

public:
  static RandomChoiceMind::Ptr create();

private:
  RandomChoiceMind();

  virtual void thinkOfMove(Checkers::Engine::MoveReceiver::Ptr aPtr);
  virtual void doStep();

private:
  Checkers::Engine::MoveReceiver::Ptr m_move_receiver;
};

#endif //H_RANDOM_CHOICE_MIND_H
