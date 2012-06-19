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

      class ErrorBusySquare : public Engine::Error
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

      class ErrorIncompleteCoordSequence : public Engine::Error
      {
      public:
        virtual void raise() const
        {
          throw *this;
        }
      };

      static const int KCoordSequenceIdAny;

      enum Type
      {
        ESimple
      , EJump
      };

    public:
      Move();
      Move(const Engine::Board &aFrom, const Engine::Board &aTo, int aCoordSequenceId = KCoordSequenceIdAny);
      Move(const Engine::Error::Ptr aError);
      Move(const Engine::Move &aMove);

      int score() const;
      Type type() const;

      void setCoordSequenceId(int aId);
      int coordSequenceId() const;
      bool anyCoordSequence() const;

      Move & operator=(const Engine::Move &aMove);

      bool operator==(const Engine::Move &aMove) const;
      bool operator!=(const Engine::Move &aMove) const;

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
      int m_coord_sequence_id;
    };
  };
};

#endif //H_MOVE_H
