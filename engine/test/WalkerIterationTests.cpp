#include "WalkerIterationTests.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( WalkerIterationTests );


void WalkerIterationTests::setUp()
{
  m_incrementor_ptr = Incrementor::create();
  m_decrementor_ptr = Decrementor::create();
  m_remover_ptr = Remover::create();
  m_batch_remover_ptr = BatchRemover::create();
  m_self_inserter_ptr = SelfInserter::create();
  CPPUNIT_ASSERT(Loop::Iteration::instance().isEmpty());
}

void WalkerIterationTests::tearDown()
{
  Loop::Iteration::instance().removeAll();
  CPPUNIT_ASSERT(Loop::Iteration::instance().isEmpty());
  m_incrementor_ptr.reset();
  m_decrementor_ptr.reset();
  m_remover_ptr->setToRemove(Loop::Walker::Ptr());
  m_remover_ptr.reset();
  m_batch_remover_ptr.reset();
  m_self_inserter_ptr.reset();
}

void WalkerIterationTests::addWalkAndSleep()
{
  m_incrementor_ptr->registerForNextIteration();
  m_decrementor_ptr->registerForNextIteration(false);
  CPPUNIT_ASSERT(!Loop::Iteration::instance().isEmpty());

  CPPUNIT_ASSERT_EQUAL(0, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(0, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(0, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(2, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(0, m_decrementor_ptr->value());

  m_decrementor_ptr->readyToGo();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(3, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-1, m_decrementor_ptr->value());

  m_incrementor_ptr->sleep();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(3, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());

  m_decrementor_ptr->sleep();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(3, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(3, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());
}

void WalkerIterationTests::addSelfFromDoStep()
{
  m_self_inserter_ptr->registerForNextIteration();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_self_inserter_ptr->value()); //No infinitive loop!
}

void WalkerIterationTests::removeItselfFromDoStep()
{
  m_incrementor_ptr->registerForNextIteration();
  m_remover_ptr->registerForNextIteration();
  m_decrementor_ptr->registerForNextIteration();

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(1, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-1, m_decrementor_ptr->value());

  m_remover_ptr->setToRemove(m_remover_ptr);
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(2, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(2, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(3, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(2, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-3, m_decrementor_ptr->value());

  m_remover_ptr->readyToGo();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(4, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(2, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-4, m_decrementor_ptr->value());
}

void WalkerIterationTests::removeAnotherFromDoStep()
{
  m_incrementor_ptr->registerForNextIteration();
  m_remover_ptr->registerForNextIteration();
  m_decrementor_ptr->registerForNextIteration();

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(1, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-1, m_decrementor_ptr->value());

  m_remover_ptr->setToRemove(m_incrementor_ptr);
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(2, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(3, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-3, m_decrementor_ptr->value());

  m_remover_ptr->setToRemove(m_decrementor_ptr);
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(4, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-4, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(5, m_remover_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-4, m_decrementor_ptr->value());
}

void WalkerIterationTests::removeAllFromDoStep()
{
  m_incrementor_ptr->registerForNextIteration();
  m_batch_remover_ptr->registerForNextIteration(false);
  m_decrementor_ptr->registerForNextIteration();

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-1, m_decrementor_ptr->value());

  m_batch_remover_ptr->readyToGo();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());

  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT(Loop::Iteration::instance().isEmpty());
  CPPUNIT_ASSERT_EQUAL(1, m_incrementor_ptr->value());
  CPPUNIT_ASSERT_EQUAL(-2, m_decrementor_ptr->value());
}
