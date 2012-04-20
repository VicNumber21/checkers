#ifndef H_MAYBE_H
#define H_MAYBE_H

#include <set>


namespace Checkers
{
  namespace Engine
  {
    template <class T>
    class Maybe
    {
    public:
      typedef T Type;
      class ErrorNothingUsed {};

    public:
      Maybe();
      Maybe(const T &aX);
      Maybe(const Maybe<T> &aMaybe);

      static Maybe<T> nothing();
      static Maybe<T> just(const T &aX);

      bool isNothing() const;
      T & operator()();
      const T & operator()() const;
      Maybe<T> & operator=(const T &aX);
      Maybe<T> & operator=(const Maybe<T> &aMaybe);

    private:
      T m_x;
      bool m_just;
    };
  };
};

#endif //H_MAYBE_H
