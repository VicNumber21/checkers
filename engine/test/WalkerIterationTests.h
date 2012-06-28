#ifndef H_WALKER_ITERATION_TESTS_H
#define H_WALKER_ITERATION_TESTS_H

#include <cppunit/extensions/HelperMacros.h>

#include "WalkerIterationTestsMocs.h"


class WalkerIterationTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( WalkerIterationTests );
    CPPUNIT_TEST( addWalkAndSleep );
    CPPUNIT_TEST( addSelfFromDoStep );
    CPPUNIT_TEST( removeItselfFromDoStep );
    CPPUNIT_TEST( removeAnotherFromDoStep );
    CPPUNIT_TEST( removeAllFromDoStep );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void addWalkAndSleep();
  void addSelfFromDoStep();
  void removeItselfFromDoStep();
  void removeAnotherFromDoStep();
  void removeAllFromDoStep();

private:
  Incrementor::Ptr m_incrementor_ptr;
  Decrementor::Ptr m_decrementor_ptr;
  Remover::Ptr m_remover_ptr;
  BatchRemover::Ptr m_batch_remover_ptr;
  SelfInserter::Ptr m_self_inserter_ptr;
};

#endif //H_WALKER_ITERATION_TESTS_H
