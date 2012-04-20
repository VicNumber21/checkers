#include "Maybe.h"
#include "Draught.h"

using namespace Checkers::Engine;


template <class T>
Maybe<T>::Maybe()
  : m_x()
  , m_just(false)
{
}

template <class T>
Maybe<T>::Maybe(const Maybe<T> &aMaybe)
  : m_x(aMaybe.m_x)
  , m_just(aMaybe.m_just)
{
}

template <class T>
Maybe<T>::Maybe(const T &aX)
  : m_x(aX)
  , m_just(true)
{
}

template <class T>
Maybe<T> Maybe<T>::nothing()
{
  return Maybe<T>();
}

template <class T>
Maybe<T> Maybe<T>::just(const T &aX)
{
  return Maybe<T>(aX);
}

template <class T>
bool Maybe<T>::isNothing() const
{
  return !m_just;
}

template <class T>
T & Maybe<T>::operator()()
{
  if(isNothing())
    throw(ErrorNothingUsed());
  return m_x;
}

template <class T>
const T & Maybe<T>::operator()() const
{
  if(isNothing())
    throw(ErrorNothingUsed());
  return m_x;
}
template <class T>
Maybe<T> & Maybe<T>::operator=(const T &aX)
{
  m_x = aX;
  m_just = true;
  return *this;
}

template <class T>
Maybe<T> & Maybe<T>::operator=(const Maybe<T> &aMaybe)
{
  m_x = aMaybe.m_x;
  m_just = aMaybe.m_just;
  return *this;
}


template class Maybe<Draught>;
