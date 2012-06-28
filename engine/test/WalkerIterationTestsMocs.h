#ifndef H_WALKER_ITERATION_TESTS_MOCS_H
#define H_WALKER_ITERATION_TESTS_MOCS_H

#include "Walker.h"
#include "Iteration.h"


class Incrementor : public Checkers::Engine::Loop::Walker<Incrementor>
{
public:
  static Incrementor::Ptr create()
  {
    Incrementor::Ptr self(new Incrementor);
    self->setSelf(self);
    return self;
  }

  virtual void doStep()
  {
    ++m_value;
  }

  int value() const
  {
    return m_value;
  }

protected:
  Incrementor() : m_value(0) {}

private:
  int m_value;
};

class Decrementor : public Checkers::Engine::Loop::Walker<Decrementor>
{
public:
  static Decrementor::Ptr create()
  {
    Decrementor::Ptr self(new Decrementor);
    self->setSelf(self);
    return self;
  }

  virtual void doStep()
  {
    --m_value;
  }

  int value() const
  {
    return m_value;
  }

private:
  Decrementor() : m_value(0) {}

private:
  int m_value;
};

class Remover : public Incrementor
{
public:
  typedef std::tr1::shared_ptr<Remover> Ptr;

public:
  static Remover::Ptr create()
  {
    Remover::Ptr self(new Remover);
    self->setSelf(self);
    return self;
  }

  virtual void doStep()
  {
    Incrementor::doStep();

    if(m_to_remove)
      m_to_remove->removeFromIteration();
  }

  void setToRemove(Checkers::Engine::Loop::WalkerBase::Ptr aToRemove)
  {
    m_to_remove = aToRemove;

    if(m_to_remove)
      readyToGo();
    else
      sleep();
  }

private:
  Remover() {}

private:
  Checkers::Engine::Loop::WalkerBase::Ptr m_to_remove;
};

class BatchRemover : public Checkers::Engine::Loop::Walker<BatchRemover>
{
  public:
    static BatchRemover::Ptr create()
    {
      BatchRemover::Ptr self(new BatchRemover);
      self->setSelf(self);
      return self;
    }

    virtual void doStep()
    {
      Checkers::Engine::Loop::Iteration::instance().removeAll(false);
      sleep();
    }

  private:
    BatchRemover() {}
};

class SelfInserter : public Incrementor
{
public:
  typedef std::tr1::shared_ptr<SelfInserter> Ptr;

public:
  static SelfInserter::Ptr create()
  {
    SelfInserter::Ptr self(new SelfInserter);
    self->setSelf(self);
    return self;
  }

  virtual void doStep()
  {
    Incrementor::doStep();

    SelfInserter::Ptr anotherSelfInserter = SelfInserter::create();
    anotherSelfInserter->registerForNextIteration();
  }

private:
  SelfInserter() {}
};

#endif //H_WALKER_ITERATION_TESTS_MOCS_H
