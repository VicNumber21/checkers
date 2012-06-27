#ifndef H_WALKER_H
#define H_WALKER_H

#include "Error.h"

#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    namespace Loop
    {
      class Walker
      {
      public:
        class Error : public Engine::Error
        {
        };

      public:
        typedef std::tr1::shared_ptr<Loop::Walker> Ptr;

      public:
        bool isReadyToGo() const;
        void readyToGo();
        void sleep();

        void registerForNextIteration(bool aSetReadyToGo = true);
        void removeFromIteration();

        bool isWaitingForRemoval() const;
        void removed();

        virtual void doStep() = 0;

      protected:
        Walker();
        void setSelf(const Walker::Ptr &aSelf);

      private:
        typedef std::tr1::weak_ptr<Loop::Walker> WeakPtr;

      private:
        Walker::WeakPtr m_self;
        bool m_ready_to_go;
        bool m_registered;
        bool m_waiting_for_removal;
      };
    };
  };
};

#endif //H_WALKER_H
