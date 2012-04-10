
#include "CoordTests.h"
#include "Coord.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( CoordTests );


void CoordTests::setUp()
{
}

void CoordTests::tearDown()
{
}

void CoordTests::wrongIntCoord()
{
  CPPUNIT_ASSERT_THROW(Coord(-1, 3), Coord::ErrorIntWrongCoord);
  CPPUNIT_ASSERT_THROW(Coord(1, -3), Coord::ErrorIntWrongCoord);
}

void CoordTests::wrongCharCoord()
{
  CPPUNIT_ASSERT_THROW(Coord('1', '2'), Coord::ErrorCharWrongCoord);
  CPPUNIT_ASSERT_THROW(Coord('a', 'b'), Coord::ErrorCharWrongCoord);
}

void CoordTests::noValueUse()
{
  Coord c;
  CPPUNIT_ASSERT_THROW(c.x(), Coord::ErrorNoValue);
}

void CoordTests::less()
{
  Coord l1(1,2);
  Coord g1(2,1);
  Coord g2(1,3);
  Coord g3(3,5);
  CPPUNIT_ASSERT(l1 < g1);
  CPPUNIT_ASSERT(l1 < g2);
  CPPUNIT_ASSERT(l1 < g3);
}

void CoordTests::equal()
{
  Coord c1(5, 6);
  Coord c2('f', '7');
  Coord c3(c1);
  CPPUNIT_ASSERT(c1 == c2);
  CPPUNIT_ASSERT(c1 == c3);
}

void CoordTests::greater()
{
  Coord l1(1,6);
  Coord g1(2,1);
  Coord g2(1,7);
  Coord g3(7,7);
  CPPUNIT_ASSERT(g1 > l1);
  CPPUNIT_ASSERT(g2 > l1);
  CPPUNIT_ASSERT(g3 > l1);
}

void CoordTests::setWrongIntCoord()
{
  Coord c;
  CPPUNIT_ASSERT_THROW(c.set(-6, 3), Coord::ErrorIntWrongCoord);
  CPPUNIT_ASSERT_THROW(c.set(4, -2), Coord::ErrorIntWrongCoord);
}

void CoordTests::setWrongCharCoord()
{
  Coord c;
  CPPUNIT_ASSERT_THROW(c.set('c', 'd'), Coord::ErrorCharWrongCoord);
  CPPUNIT_ASSERT_THROW(c.set('4', '8'), Coord::ErrorCharWrongCoord);
}

void CoordTests::normalCase()
{
  Coord c1(3, 5);
  CPPUNIT_ASSERT_EQUAL(c1.letter(), 'd');
  CPPUNIT_ASSERT_EQUAL(c1.digit(), '6');

  Coord c2('a', '6');
  CPPUNIT_ASSERT_EQUAL(c2.x(), 0);
  CPPUNIT_ASSERT_EQUAL(c2.y(), 5);
}
