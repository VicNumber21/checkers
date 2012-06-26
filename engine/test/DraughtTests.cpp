#include "DraughtTests.h"
#include "RulesOfGameManager.h"
#include "RulesOfGameInstances.h"
#include "Draught.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( DraughtTests );


void DraughtTests::setUp()
{
  RulesOfGameManager::instance().append(RulesOfGameInstanceInterface::Ptr(new AmericanCheckersRulesOfGame), true);
}

void DraughtTests::tearDown()
{
  RulesOfGameManager::instance().reset();
}

void DraughtTests::coordAndColor()
{
  Draught d(Coord('b','8'), Color(Color::EBlack));
  CPPUNIT_ASSERT(d.color() == Color::EBlack);
  CPPUNIT_ASSERT(d.coord() == Coord('b','8'));
}

void DraughtTests::theSameCoordDifferentColor()
{
  Draught d1(Coord('f','3'), Color(Color::EBlack));
  Draught d2(Coord('f','3'), Color(Color::EWhite));
  CPPUNIT_ASSERT(d1.color() != d2.color());
  CPPUNIT_ASSERT(d1.coord() == d2.coord());
}

void DraughtTests::theSameColorDifferentCoord()
{
  Draught d1(Coord('f','3'), Color(Color::EBlack));
  Draught d2(Coord('c','1'), Color(Color::EBlack));
  CPPUNIT_ASSERT(d1.color() == d2.color());
  CPPUNIT_ASSERT(d1.coord() != d2.coord());
}

void DraughtTests::equal()
{
  Draught d1(Coord('a','7'), Color(Color::EBlack));
  Draught d2(Coord('a','7'), Color(Color::EBlack));
  Draught d3(Coord('a','7'), Color(Color::EWhite));
  Draught d4(Coord('g','7'), Color(Color::EBlack));
  CPPUNIT_ASSERT(d1 == d2);
  CPPUNIT_ASSERT(!(d1 == d3));
  CPPUNIT_ASSERT(!(d1 == d4));
  d2.makeKing();
  CPPUNIT_ASSERT(!(d1 == d2));
}

void DraughtTests::notEqual()
{
  Draught d1(Coord('a','7'), Color(Color::EBlack));
  Draught d2(Coord('a','7'), Color(Color::EBlack));
  Draught d3(Coord('a','7'), Color(Color::EWhite));
  Draught d4(Coord('g','7'), Color(Color::EBlack));
  CPPUNIT_ASSERT(d1 != d3);
  CPPUNIT_ASSERT(d1 != d4);
  CPPUNIT_ASSERT(!(d1 != d2));
  d2.makeKing();
  CPPUNIT_ASSERT(d1 != d2);
}

void DraughtTests::bigger()
{
  Draught d1(Coord('a','7'), Color(Color::EBlack));
  Draught d2(Coord('a','7'), Color(Color::EBlack));
  Draught d3(Coord('a','7'), Color(Color::EWhite));
  Draught d4(Coord('g','7'), Color(Color::EBlack));
  Draught d5(Coord('c','8'), Color(Color::EBlack));
  CPPUNIT_ASSERT(d4 > d3);
  CPPUNIT_ASSERT(d4 > d1);
  CPPUNIT_ASSERT(d4 > d5);
  CPPUNIT_ASSERT(!(d1 > d3));
  CPPUNIT_ASSERT(!(d1 > d2));
  CPPUNIT_ASSERT(!(d5 > d4));
  d5.makeKing();
  CPPUNIT_ASSERT(d4 > d5);
  CPPUNIT_ASSERT(!(d5 > d4));
}

void DraughtTests::less()
{
  Draught d1(Coord('a','7'), Color(Color::EBlack));
  Draught d2(Coord('a','7'), Color(Color::EBlack));
  Draught d3(Coord('a','7'), Color(Color::EWhite));
  Draught d4(Coord('g','7'), Color(Color::EBlack));
  Draught d5(Coord('c','8'), Color(Color::EBlack));
  CPPUNIT_ASSERT(d3 < d4);
  CPPUNIT_ASSERT(d1 < d4);
  CPPUNIT_ASSERT(d5 < d4);
  CPPUNIT_ASSERT(!(d3 < d1));
  CPPUNIT_ASSERT(!(d2 < d1));
  CPPUNIT_ASSERT(!(d4 < d5));
  d5.makeKing();
  CPPUNIT_ASSERT(d5 < d4);
  CPPUNIT_ASSERT(!(d4 < d5));
}

void DraughtTests::moveTo()
{
  Draught d(Coord('a','7'), Color(Color::EBlack), true);
  d.moveTo(Coord('b','6'));
  CPPUNIT_ASSERT(d.coord() == Coord('b','6'));
  CPPUNIT_ASSERT(d.color() == Color::EBlack);
  CPPUNIT_ASSERT(d.isKing());
}

void DraughtTests::makeKing()
{
  Draught d(Coord('c','4'), Color(Color::EWhite));
  d.makeKing();
  CPPUNIT_ASSERT(d.coord() == Coord('c','4'));
  CPPUNIT_ASSERT(d.color() == Color::EWhite);
  CPPUNIT_ASSERT(d.isKing());
}
