#ifndef H_WALKER_BASE_H
#define H_WALKER_BASE_H

#include "Error.h"

#include <tr1/memory>


namespace Checkers
{
  namespace Engine
  {
    namespace Loop
    {
      class WalkerBase
      {
      public:
        class Error : public Engine::Error
        {
        };

      public:
        typedef std::tr1::shared_ptr<Loop::WalkerBase> Ptr;

      public:
        bool isReadyToGo() const;
        void readyToGo();
        void sleep();

        void removeFromIteration();

        bool isWaitingForRemoval() const;
        void removed();

        virtual void doStep() = 0;

      protected:
        WalkerBase();

        void registerForNextIteration(Loop::WalkerBase::Ptr aPtr, bool aSetReadyToGo = true);

      private:
        bool m_ready_to_go;
        bool m_registered;
        bool m_waiting_for_removal;
      };
    };
  };
};

#endif //H_WALKER_BASE_H
