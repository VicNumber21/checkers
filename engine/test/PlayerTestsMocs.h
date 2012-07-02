#ifndef H_PLAYER_TESTS_MOCS_H
#define H_PLAYER_TESTS_MOCS_H

#include "Walker.h"
#include "PlayerMind.h"
#include "CoordSequence.h"


class IKnowThreeMoveMind : public Checkers::Engine::Loop::Walker<IKnowThreeMoveMind>
                         , public Checkers::Engine::PlayerMind
{
public:
  typedef Checkers::Engine::Loop::Walker<IKnowThreeMoveMind>::Ptr Ptr;

  class Error : public Checkers::Engine::Error
  {
  };

public:
  static IKnowThreeMoveMind::Ptr create()
  {
    IKnowThreeMoveMind::Ptr self(new IKnowThreeMoveMind);
    self->setSelf(self);
    return self;
  }

  bool doesKnowAnythingElse() const
  {
    return count() < 7;
  }

  int count() const
  {
    return m_count;
  }

private:
  IKnowThreeMoveMind() : m_count(0) {}

  virtual void thinkOfMove(Checkers::Engine::MoveReceiver::Ptr aPtr)
  {
    if(isReadyToGo())
      throw IKnowThreeMoveMind::Error();

    m_move_receiver = aPtr;
    readyToGo();
  }

  virtual void doStep()
  {
    Checkers::Engine::CoordSequence csMove;

    switch(m_count)
    {
      case 0:
        csMove = Checkers::Engine::CoordSequence(Checkers::Engine::Coord('c', '3'), Checkers::Engine::Coord('d', '4'));
        ++m_count;
        break;

      case 1:
        csMove = Checkers::Engine::CoordSequence(Checkers::Engine::Coord('b', '6'), Checkers::Engine::Coord('a', '5'));
        ++m_count;
        break;

      case 2:
        csMove = Checkers::Engine::CoordSequence(Checkers::Engine::Coord('a', '3'), Checkers::Engine::Coord('b', '4'));
        ++m_count;
        break;

      case 3:
        csMove = Checkers::Engine::CoordSequence(Checkers::Engine::Coord('a', '5'), Checkers::Engine::Coord('c', '3'));
        ++m_count;
        break;

      case 4:
        csMove = Checkers::Engine::CoordSequence(Checkers::Engine::Coord('d', '2'), Checkers::Engine::Coord('b', '4'));
        ++m_count;
        break;

      case 5:
        csMove = Checkers::Engine::CoordSequence(Checkers::Engine::Coord('h', '6'), Checkers::Engine::Coord('g', '5'));
        ++m_count;
        break;

      case 6:
        ++m_count;
        break;

      default:
        break;
    };

    if(doesKnowAnythingElse() && !m_move_receiver.expired())
    {
      m_move_receiver.lock()->set(csMove);
    }

    sleep();
  }

private:
  int m_count;
  Checkers::Engine::MoveReceiver::Ptr m_move_receiver;
};

class RemoteControlMind : public Checkers::Engine::Loop::Walker<RemoteControlMind>
                         , public Checkers::Engine::PlayerMind
{
public:
  typedef Checkers::Engine::Loop::Walker<RemoteControlMind>::Ptr Ptr;

  class Error : public Checkers::Engine::Error
  {
  };

public:
  static RemoteControlMind::Ptr create()
  {
    RemoteControlMind::Ptr self(new RemoteControlMind);
    self->setSelf(self);
    return self;
  }

  int count() const
  {
    return m_count;
  }

  void setMove(const Checkers::Engine::CoordSequence &aMove)
  {
    m_move = aMove;
    readyToGo();
  }

  void setMoveTest(const Checkers::Engine::CoordSequence &aMove)
  {
    m_move_receiver.lock()->set(aMove);
  }

  Checkers::Engine::Color requestedColor() const
  {
    return m_move_receiver.lock()->color();
  }

private:
  RemoteControlMind() : m_count(0) {}

  virtual void thinkOfMove(Checkers::Engine::MoveReceiver::Ptr aPtr)
  {
    if(isReadyToGo())
      throw RemoteControlMind::Error();

    m_move_receiver = aPtr;
    readyToGo();
  }

  virtual void doStep()
  {
    ++m_count;

    if(giveMove() && !m_move_receiver.expired())
    {
      m_move_receiver.lock()->set(m_move);
      m_move = Checkers::Engine::CoordSequence();
    }

    sleep();
  }

  bool giveMove()
  {
    return m_move.count() >= 2;
  }

private:
  int m_count;
  Checkers::Engine::CoordSequence m_move;
  Checkers::Engine::MoveReceiver::Ptr m_move_receiver;
};

#endif //H_PLAYER_TESTS_MOCS_H
