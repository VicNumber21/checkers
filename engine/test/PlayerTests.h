#ifndef H_PLAYER_TESTS_H
#define H_PLAYER_TESTS_H

#include <cppunit/extensions/HelperMacros.h>


class PlayerTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( PlayerTests );
    CPPUNIT_TEST( thinkAndMakeMove );
    CPPUNIT_TEST( stepByStep );
    CPPUNIT_TEST( randomChoiceMindVsItself );
    CPPUNIT_TEST( randomChoiceMindVsJustOwnMoveAheadMind );
    CPPUNIT_TEST( justOwnMoveAheadMindVsItself );
    CPPUNIT_TEST( justOwnMoveAheadMindVsRandomChoiceMind );
  CPPUNIT_TEST_SUITE_END();

public:
  virtual void setUp();
  virtual void tearDown();

  void thinkAndMakeMove();
  void stepByStep();
  //TODO move mind tests into another suite?
  void randomChoiceMindVsItself();
  void randomChoiceMindVsJustOwnMoveAheadMind();
  void justOwnMoveAheadMindVsItself();
  void justOwnMoveAheadMindVsRandomChoiceMind();
};

#endif //H_PLAYER_TESTS_H
