#include "BoardTests.h"
#include "RulesOfGameManager.h"
#include "RulesOfGameInstances.h"
#include "Board.h"
#include "Draught.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( BoardTests );


void BoardTests::setUp()
{
  RulesOfGameManager::instance().append(RulesOfGameInstanceInterface::Ptr(new AmericanCheckersRulesOfGame), true);
}

void BoardTests::tearDown()
{
  RulesOfGameManager::instance().reset();
}

void BoardTests::put()
{
  Board b;
  Draught d1(Coord('b','8'), Color::EBlack, true);
  Draught d2(Coord('a','6'), Color::EWhite);
  Draught d3(Coord('a','6'), Color::EBlack);
  Draught d4(Coord('a','6'), Color::EWhite, true);
  Draught d5(Coord('g','1'), Color::EWhite, true);

  CPPUNIT_ASSERT(b.put(d1));
  CPPUNIT_ASSERT_EQUAL(1, b.count());
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EWhite));
  Maybe<Draught> md1 = b.testSquare(Coord('b','8'));
  CPPUNIT_ASSERT(!md1.isNothing());
  CPPUNIT_ASSERT(d1 == md1());

  CPPUNIT_ASSERT(b.put(d2));
  CPPUNIT_ASSERT_EQUAL(2, b.count());
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));
  Maybe<Draught> md2 = b.testSquare(Coord('a','6'));
  CPPUNIT_ASSERT(!md2.isNothing());
  CPPUNIT_ASSERT(d2 == md2());

  CPPUNIT_ASSERT(!b.put(d3));
  CPPUNIT_ASSERT_EQUAL(2, b.count());
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));
  Maybe<Draught> md3 = b.testSquare(Coord('a','6'));
  CPPUNIT_ASSERT(!md3.isNothing());
  CPPUNIT_ASSERT(d2 == md3());
  CPPUNIT_ASSERT(d3 != md3());

  CPPUNIT_ASSERT(!b.put(d4));
  CPPUNIT_ASSERT_EQUAL(2, b.count());
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));
  Maybe<Draught> md4 = b.testSquare(Coord('a','6'));
  CPPUNIT_ASSERT(!md4.isNothing());
  CPPUNIT_ASSERT(d2 == md4());
  CPPUNIT_ASSERT(d3 != md4());
  CPPUNIT_ASSERT(d4 != md4());

  CPPUNIT_ASSERT(b.put(d5));
  CPPUNIT_ASSERT_EQUAL(3, b.count());
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(2, b.count(Color::EWhite));
  Maybe<Draught> md5 = b.testSquare(Coord('g','1'));
  CPPUNIT_ASSERT(!md5.isNothing());
  CPPUNIT_ASSERT(d5 == md5());
}

void BoardTests::putManOnKingRow()
{
  Board b;
  Draught d1(Coord('g','1'), Color::EWhite);
  Draught d2(Coord('b','8'), Color::EBlack);

  CPPUNIT_ASSERT(!b.put(d1));
  CPPUNIT_ASSERT(!b.put(d2));
}

void BoardTests::takeDraught()
{
  Board b;
  Draught d1(Coord('g','3'), Color::EWhite);
  b.put(d1);

  Maybe<Draught> md1 = b.takeDraught(Coord('g','4'));
  CPPUNIT_ASSERT(md1.isNothing());
  CPPUNIT_ASSERT_EQUAL(1, b.count());
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));

  Maybe<Draught> md2 = b.takeDraught(Coord('g','3'));
  CPPUNIT_ASSERT(!md2.isNothing());
  CPPUNIT_ASSERT(d1 == md2());
  CPPUNIT_ASSERT_EQUAL(0, b.count());
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EWhite));

  Maybe<Draught> md3 = b.takeDraught(Coord('g','3'));
  CPPUNIT_ASSERT(md3.isNothing());
  CPPUNIT_ASSERT_EQUAL(0, b.count());
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EWhite));
}

void BoardTests::testSquare()
{
  Board b;
  Draught d1(Coord('g','3'), Color::EWhite);
  b.put(d1);

  Maybe<Draught> md1 = b.testSquare(Coord('g','4'));
  CPPUNIT_ASSERT(md1.isNothing());
  CPPUNIT_ASSERT_EQUAL(1, b.count());
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));

  Maybe<Draught> md2 = b.testSquare(Coord('g','3'));
  CPPUNIT_ASSERT(!md2.isNothing());
  CPPUNIT_ASSERT(d1 == md2());
  CPPUNIT_ASSERT_EQUAL(1, b.count());
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));

  Maybe<Draught> md3 = b.testSquare(Coord('g','3'));
  CPPUNIT_ASSERT(!md3.isNothing());
  CPPUNIT_ASSERT(d1 == md3());
  CPPUNIT_ASSERT(md2() == md3());
  CPPUNIT_ASSERT_EQUAL(1, b.count());
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));
}

void BoardTests::equal()
{
  Board b1;
  Board b2;
  CPPUNIT_ASSERT(b1 == b2);
  Draught d1(Coord('b','4'), Color::EWhite);
  b1.put(d1);
  CPPUNIT_ASSERT(!(b1 == b2));
  b2.put(d1);
  CPPUNIT_ASSERT(b1 == b2);

  Draught d2(Coord('c','6'), Color::EBlack);
  b1.put(d2);
  CPPUNIT_ASSERT(!(b1 == b2));
  b2.put(d2);
  CPPUNIT_ASSERT(b1 == b2);

  Board b3(b1);
  CPPUNIT_ASSERT(b1 == b3);
  Draught d3(Coord('f','1'), Color::EBlack);
  Draught d4(Coord('f','1'), Color::EWhite);
  b1.put(d3);
  CPPUNIT_ASSERT(!(b1 == b3));
  b3.put(d4);
  CPPUNIT_ASSERT(!(b1 == b3));

  Board b4(b1);
  CPPUNIT_ASSERT(b1 == b4);
  Draught d5(Coord('h','2'), Color::EBlack);
  Draught d6(Coord('h','2'), Color::EBlack, true);
  b1.put(d5);
  CPPUNIT_ASSERT(!(b1 == b4));
  b4.put(d6);
  CPPUNIT_ASSERT(!(b1 == b4));
}

void BoardTests::notEqual()
{
  Board b1;
  Board b2;
  CPPUNIT_ASSERT(!(b1 != b2));
  Draught d1(Coord('a','4'), Color::EWhite);
  b1.put(d1);
  CPPUNIT_ASSERT(b1 != b2);
  b2.put(d1);
  CPPUNIT_ASSERT(!(b1 != b2));

  Draught d2(Coord('d','7'), Color::EBlack);
  b1.put(d2);
  CPPUNIT_ASSERT(b1 != b2);
  b2.put(d2);
  CPPUNIT_ASSERT(!(b1 != b2));

  Board b3(b1);
  CPPUNIT_ASSERT(!(b1 != b3));
  Draught d3(Coord('e','5'), Color::EBlack);
  Draught d4(Coord('e','5'), Color::EWhite);
  b1.put(d3);
  CPPUNIT_ASSERT(b1 != b3);
  b3.put(d4);
  CPPUNIT_ASSERT(b1 != b3);

  Board b4(b1);
  CPPUNIT_ASSERT(!(b1 != b4));
  Draught d5(Coord('g','6'), Color::EBlack);
  Draught d6(Coord('g','6'), Color::EBlack, true);
  b1.put(d5);
  CPPUNIT_ASSERT(b1 != b4);
  b4.put(d6);
  CPPUNIT_ASSERT(b1 != b4);
}

void BoardTests::less()
{
  Board b1;
  Board b2;
  CPPUNIT_ASSERT(!(b1 < b2));
  CPPUNIT_ASSERT(!(b2 < b1));
  Draught d1(Coord('a','4'), Color::EWhite);
  b1.put(d1);
  CPPUNIT_ASSERT(!(b1 < b2));
  CPPUNIT_ASSERT(b2 < b1);
  b2.put(d1);
  CPPUNIT_ASSERT(!(b1 < b2));
  CPPUNIT_ASSERT(!(b2 < b1));

  Draught d2(Coord('d','7'), Color::EBlack);
  b1.put(d2);
  CPPUNIT_ASSERT(!(b1 < b2));
  CPPUNIT_ASSERT(b2 < b1);
  b2.put(d2);
  CPPUNIT_ASSERT(!(b1 < b2));
  CPPUNIT_ASSERT(!(b2 < b1));

  Board b3(b1);
  Draught d3(Coord('e','5'), Color::EBlack);
  Draught d4(Coord('e','5'), Color::EWhite);
  b1.put(d3);
  CPPUNIT_ASSERT(!(b1 < b3));
  CPPUNIT_ASSERT(b3 < b1);
  b3.put(d4);
  CPPUNIT_ASSERT(b1 < b3);
  CPPUNIT_ASSERT(!(b3 < b1));
  Draught d7(Coord('f','8'), Color::EWhite);
  b1.put(d7);
  CPPUNIT_ASSERT(!(b1 < b3));
  CPPUNIT_ASSERT(b3 < b1);

  Board b4(b1);
  Draught d5(Coord('g','6'), Color::EBlack);
  Draught d6(Coord('g','6'), Color::EBlack, true);
  b1.put(d5);
  CPPUNIT_ASSERT(!(b1 < b4));
  CPPUNIT_ASSERT(b4 < b1);
  b4.put(d6);
  CPPUNIT_ASSERT(b1 < b4);
  CPPUNIT_ASSERT(!(b4 < b1));
  Draught d8(Coord('b','4'), Color::EWhite);
  b1.put(d8);
  CPPUNIT_ASSERT(!(b1 < b4));
  CPPUNIT_ASSERT(b4 < b1);
}

void BoardTests::lessBugTest()
{
  const Coord c3('c', '3');
  const Coord d4('d', '4');

  Board b1;
  Board b2;
  b1.put(Draught(c3, Color::EBlack, true));
  b2.put(Draught(c3, Color::EWhite));
  CPPUNIT_ASSERT(b1 < b2);
  CPPUNIT_ASSERT(!(b2 < b1));

  Board b3;
  Board b4;
  b3.put(Draught(c3, Color::EWhite));
  b4.put(Draught(d4, Color::EBlack));
  CPPUNIT_ASSERT(b3 < b4);
  CPPUNIT_ASSERT(!(b4 < b3));
}

void BoardTests::bigger()
{
  Board b1;
  Board b2;
  CPPUNIT_ASSERT(!(b1 > b2));
  CPPUNIT_ASSERT(!(b1 > b2));
  Draught d1(Coord('a','4'), Color::EWhite);
  b1.put(d1);
  CPPUNIT_ASSERT(!(b2 > b1));
  CPPUNIT_ASSERT(b1 > b2);
  b2.put(d1);
  CPPUNIT_ASSERT(!(b1 > b2));
  CPPUNIT_ASSERT(!(b2 > b1));

  Draught d2(Coord('d','7'), Color::EBlack);
  b1.put(d2);
  CPPUNIT_ASSERT(!(b2 > b1));
  CPPUNIT_ASSERT(b1 > b2);
  b2.put(d2);
  CPPUNIT_ASSERT(!(b1 > b2));
  CPPUNIT_ASSERT(!(b2 > b1));

  Board b3(b1);
  Draught d3(Coord('e','5'), Color::EBlack);
  Draught d4(Coord('e','5'), Color::EWhite);
  b1.put(d3);
  CPPUNIT_ASSERT(!(b3 > b1));
  CPPUNIT_ASSERT(b1 > b3);
  b3.put(d4);
  CPPUNIT_ASSERT(b3 > b1);
  CPPUNIT_ASSERT(!(b1 > b3));
  Draught d7(Coord('f','8'), Color::EWhite);
  b1.put(d7);
  CPPUNIT_ASSERT(!(b3 > b1));
  CPPUNIT_ASSERT(b1 > b3);

  Board b4(b1);
  Draught d5(Coord('g','6'), Color::EBlack);
  Draught d6(Coord('g','6'), Color::EBlack, true);
  b1.put(d5);
  CPPUNIT_ASSERT(!(b4 > b1));
  CPPUNIT_ASSERT(b1 > b4);
  b4.put(d6);
  CPPUNIT_ASSERT(b4 > b1);
  CPPUNIT_ASSERT(!(b1 > b4));
  Draught d8(Coord('b','4'), Color::EWhite);
  b1.put(d8);
  CPPUNIT_ASSERT(!(b4 > b1));
  CPPUNIT_ASSERT(b1 > b4);
}

void BoardTests::biggerBugTest()
{
  const Coord c3('c', '3');
  const Coord d4('d', '4');

  Board b1;
  Board b2;
  b1.put(Draught(c3, Color::EBlack, true));
  b2.put(Draught(c3, Color::EWhite));
  CPPUNIT_ASSERT(b2 > b1);
  CPPUNIT_ASSERT(!(b1 > b2));

  Board b3;
  Board b4;
  b3.put(Draught(c3, Color::EWhite));
  b4.put(Draught(d4, Color::EBlack));
  CPPUNIT_ASSERT(b4 > b3);
  CPPUNIT_ASSERT(!(b3 > b4));
}

void BoardTests::count()
{
  Board b;
  CPPUNIT_ASSERT_EQUAL(0, b.count());
  Draught d1(Coord('g','6'), Color::EBlack);
  Draught d2(Coord('a','6'), Color::EWhite);
  Draught d3(Coord('b','6'), Color::EBlack, true);
  Draught d4(Coord('c','6'), Color::EWhite, true);
  Draught d5(Coord('d','6'), Color::EBlack);

  b.put(d1);
  CPPUNIT_ASSERT_EQUAL(1, b.count());

  b.put(d2);
  CPPUNIT_ASSERT_EQUAL(2, b.count());

  b.put(d3);
  CPPUNIT_ASSERT_EQUAL(3, b.count());

  b.put(d4);
  CPPUNIT_ASSERT_EQUAL(4, b.count());

  b.put(d5);
  CPPUNIT_ASSERT_EQUAL(5, b.count());

  b.takeDraught(Coord('a','6'));
  CPPUNIT_ASSERT_EQUAL(4, b.count());
  b.takeDraught(Coord('a','6'));
  CPPUNIT_ASSERT_EQUAL(4, b.count());
}

void BoardTests::countWhite()
{
  Board b;
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EWhite));
  Draught d1(Coord('g','3'), Color::EBlack);
  Draught d2(Coord('a','6'), Color::EWhite);
  Draught d3(Coord('b','7'), Color::EBlack, true);
  Draught d4(Coord('c','1'), Color::EWhite, true);
  Draught d5(Coord('d','2'), Color::EBlack);

  b.put(d1);
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EWhite));

  b.put(d2);
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));

  b.put(d3);
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));

  b.put(d4);
  CPPUNIT_ASSERT_EQUAL(2, b.count(Color::EWhite));

  b.put(d5);
  CPPUNIT_ASSERT_EQUAL(2, b.count(Color::EWhite));

  b.takeDraught(Coord('a','6'));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));
  b.takeDraught(Coord('a','6'));
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EWhite));
}

void BoardTests::countBlack()
{
  Board b;
  CPPUNIT_ASSERT_EQUAL(0, b.count(Color::EBlack));
  Draught d1(Coord('g','3'), Color::EBlack);
  Draught d2(Coord('a','6'), Color::EWhite);
  Draught d3(Coord('b','7'), Color::EBlack, true);
  Draught d4(Coord('c','1'), Color::EWhite, true);
  Draught d5(Coord('d','2'), Color::EBlack);

  b.put(d1);
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));

  b.put(d2);
  CPPUNIT_ASSERT_EQUAL(1, b.count(Color::EBlack));

  b.put(d3);
  CPPUNIT_ASSERT_EQUAL(2, b.count(Color::EBlack));

  b.put(d4);
  CPPUNIT_ASSERT_EQUAL(2, b.count(Color::EBlack));

  b.put(d5);
  CPPUNIT_ASSERT_EQUAL(3, b.count(Color::EBlack));

  b.takeDraught(Coord('a','6'));
  CPPUNIT_ASSERT_EQUAL(3, b.count(Color::EBlack));
  b.takeDraught(Coord('a','6'));
  CPPUNIT_ASSERT_EQUAL(3, b.count(Color::EBlack));
}
