#ifndef H_ITERATION_H
#define H_ITERATION_H

#include "WalkerBase.h"

#include <list>


namespace Checkers
{
  namespace Engine
  {
    namespace Loop
    {
      class Iteration
      {
      public:
        static Iteration &instance();

        void registerForNextIteration(const Loop::WalkerBase::Ptr &aWalker);
        void removeAll(bool aNow = true);

        void walk();

        bool isEmpty() const;

      private:
        typedef std::list<Loop::WalkerBase::Ptr> WalkerStorage;

      private:
        Iteration();
        WalkerStorage::iterator removeWalker(WalkerStorage::iterator aWalker);

      private:
        WalkerStorage m_walkers;
      };
    };
  };
};

#endif //H_ITERATION_H
