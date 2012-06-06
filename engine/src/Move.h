#ifndef H_MOVE_H
#define H_MOVE_H

#include "CoordSequence.h"
#include "Board.h"
#include "Error.h"


namespace Checkers
{
  namespace Engine
  {
    class Move
    {
    public:
      class ErrorNoRequestedDraught : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorNothingToJumpOver : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorInWrongDirection : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorToBusySquare : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorJumpOverBusySquare : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorJumpExist : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorJumpOverSameColor : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorGetKingButMoveFurther : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorUnexpectedAppend : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      class ErrorUndefinedUsage : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      typedef CoordSequence::Error ErrorCoordSequence;

      class ErrorUnknown : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      enum Type
      {
        EUndefined
      , ESimple
      , EJump
      };

    public:
      Move();
      Move(const Engine::Board &aFrom, const Engine::Board &aTo);
      Move(const Engine::Error::Ptr aError);
      Move(const Engine::Coord &aStart, const Engine::Coord &aNext, Type aType = ESimple);
      Move(const Engine::Move &aMove);

      void append(const Engine::Coord &aNext);

      int score() const;
      Type type() const;

      Move & operator=(const Engine::Move &aMove);

      bool operator==(const Engine::Move &aMove) const;
      bool operator!=(const Engine::Move &aMove) const;

      const CoordSequence & coords() const;
      const Board &from() const;
      const Board &to() const;

      bool isValid() const;
      Engine::Error::Ptr error() const;

    private:
      void throwIfInvalid() const;

    private:
      Board m_from;
      Board m_to;
      Error::Ptr m_error;

      CoordSequence m_coords;
      Type m_type;
    };
  };
};

#endif //H_MOVE_H
