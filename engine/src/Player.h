#ifndef H_PLAYER_H
#define H_PLAYER_H

#include "Walker.h"
#include "MoveReceiver.h"
#include "PlayerMind.h"
#include "Move.h"
#include "Error.h"
#include "Color.h"


namespace Checkers
{
  namespace Engine
  {
    class Player : public Loop::Walker<Player>
                 , public MoveReceiver
    {
    public:
      typedef Loop::Walker<Player>::Ptr Ptr;

      //TODO rework errors
      class ErrorIsActive : public Engine::Error
      {
      };

      class ErrorIsNotWaitingForMove : public Engine::Error
      {
      };

      class ErrorWrongMoveColor : public Engine::Error
      {
      };

    public:
      static Player::Ptr create(Color aColor, PlayerMind::Ptr aMind);

      void setColor(Color aColor);
      Color color() const;

      void setMind(PlayerMind::Ptr aMind);

      void yourTurn();
      bool isThinking() const;

    protected:
      Player(Color aColor, PlayerMind::Ptr aMind);

    private:
      virtual void doStep();
      virtual void set(const Engine::CoordSequence &aCoordSequence);
      virtual void set(const Engine::Move &aMove);

      bool isReadyToMove() const;
      bool isActive() const;

      void think();
      void doMove();

      void throwIfActive() const;

    private:
      PlayerMind::Ptr m_mind;
      Color m_color;
      bool m_thinking;
      bool m_ready_to_move;
      Move m_move;
    };
  };
};

#endif //H_PLAYER_H
