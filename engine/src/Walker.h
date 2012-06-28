#ifndef H_WALKER_H
#define H_WALKER_H

#include "WalkerBase.h"


namespace Checkers
{
  namespace Engine
  {
    namespace Loop
    {
      template <class T = Loop::WalkerBase>
      class Walker : public WalkerBase
      {
      public:
        typedef std::tr1::shared_ptr<T> Ptr;

      public:
        void registerForNextIteration(bool aSetReadyToGo = true)
        {
          WalkerBase::registerForNextIteration(self(), aSetReadyToGo);
        }

      protected:
        Walker() {}

        void setSelf(const Walker<T>::Ptr &aSelf)
        {
          m_self = aSelf;
        }

        Walker<T>::Ptr self()
        {
          if(m_self.expired())
            throw WalkerBase::Error();

          return m_self.lock();
        }

      private:
        typedef std::tr1::weak_ptr<T> WeakPtr;

      private:
        Walker::WeakPtr m_self;
      };
    };
  };
};

#endif //H_WALKER_H
