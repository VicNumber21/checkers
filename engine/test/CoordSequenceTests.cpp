#include "CoordSequenceTests.h"
#include "CoordSequence.h"
#include "PrettyPrint.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( CoordSequenceTests );


void CoordSequenceTests::setUp()
{
}

void CoordSequenceTests::tearDown()
{
}

void CoordSequenceTests::wrongSequenceForSimpleMove()
{
  CPPUNIT_ASSERT_THROW(CoordSequence cs(Coord('a', '5'), Coord('b', '2')), CoordSequence::Error);
  CPPUNIT_ASSERT_THROW(CoordSequence cs(Coord('a', '2'), Coord('b', '3')), CoordSequence::Error);
}

void CoordSequenceTests::wrongSequenceForJump()
{
  CoordSequence cs1(Coord('b', '2'), Coord('c', '3'));
  CPPUNIT_ASSERT_THROW(cs1.append(Coord('e', '5')), CoordSequence::Error);

  CoordSequence cs2(Coord('f', '2'), Coord('d', '4'));
  CPPUNIT_ASSERT_THROW(cs2.append(Coord('e', '5')), CoordSequence::Error);

  CoordSequence cs3(Coord('f', '2'), Coord('d', '4'));
  CPPUNIT_ASSERT_THROW(cs3.append(Coord('f', '2')), CoordSequence::Error);
}

void CoordSequenceTests::equal()
{
  CoordSequence cs1;
  CoordSequence cs2;
  CoordSequence cs3(Coord('f', '6'), Coord('g', '5'));
  CPPUNIT_ASSERT(cs1 == cs2);
  CPPUNIT_ASSERT(!(cs1 == cs3));

  cs1 = CoordSequence(Coord('a', '3'), Coord('b', '4'));
  cs2 = CoordSequence(Coord('a', '3'), Coord('b', '4'));
  CPPUNIT_ASSERT(cs1 == cs2);
  CPPUNIT_ASSERT(!(cs1 == cs3));

  cs1 = CoordSequence(Coord('c', '5'), Coord('a', '3'));
  cs2 = CoordSequence(Coord('c', '5'), Coord('a', '3'));
  CPPUNIT_ASSERT(cs1 == cs2);
  CPPUNIT_ASSERT(!(cs1 == cs3));

  cs1.append(Coord('c', '1'));
  cs2.append(Coord('c', '1'));
  CPPUNIT_ASSERT(cs1 == cs2);
  CPPUNIT_ASSERT(!(cs1 == cs3));

  cs2.append(Coord('e', '3'));
  CPPUNIT_ASSERT(!(cs1 == cs2));
}

void CoordSequenceTests::notEqual()
{
  CoordSequence cs1;
  CoordSequence cs2;
  CoordSequence cs3(Coord('f', '6'), Coord('g', '5'));
  CPPUNIT_ASSERT(!(cs1 != cs2));
  CPPUNIT_ASSERT(cs1 != cs3);

  cs1 = CoordSequence(Coord('a', '3'), Coord('b', '4'));
  cs2 = CoordSequence(Coord('a', '3'), Coord('b', '4'));
  CPPUNIT_ASSERT(!(cs1 != cs2));
  CPPUNIT_ASSERT(cs1 != cs3);

  cs1 = CoordSequence(Coord('c', '5'), Coord('a', '3'));
  cs2 = CoordSequence(Coord('c', '5'), Coord('a', '3'));
  CPPUNIT_ASSERT(!(cs1 != cs2));
  CPPUNIT_ASSERT(cs1 != cs3);

  cs1.append(Coord('c', '1'));
  cs2.append(Coord('c', '1'));
  CPPUNIT_ASSERT(!(cs1 != cs2));
  CPPUNIT_ASSERT(cs1 != cs3);

  cs2.append(Coord('e', '3'));
  CPPUNIT_ASSERT(cs1 != cs2);
}

void CoordSequenceTests::beginAndEnd()
{
  CoordSequence cs;
  CPPUNIT_ASSERT(cs.begin() == cs.end());

  Coord c('a', '1');
  cs.append(c);
  CPPUNIT_ASSERT(cs.begin() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c, *cs.begin());

  cs.append(Coord('c', '3'));
  CPPUNIT_ASSERT(cs.begin() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c, *cs.begin());
}

void CoordSequenceTests::second()
{
  CoordSequence cs;
  CPPUNIT_ASSERT(cs.second() == cs.end());

  cs.append(Coord('e', '1'));
  CPPUNIT_ASSERT(cs.second() == cs.end());

  Coord c('c', '3');
  cs.append(c);
  CPPUNIT_ASSERT(cs.second() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c, *cs.second());

  cs.append(Coord('a', '5'));
  CPPUNIT_ASSERT(cs.second() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c, *cs.second());
}

void CoordSequenceTests::thirdFromEnd()
{
  CoordSequence cs;
  CPPUNIT_ASSERT(cs.thirdFromEnd() == cs.end());

  Coord c1('e', '1');
  cs.append(c1);
  CPPUNIT_ASSERT(cs.thirdFromEnd() == cs.end());

  Coord c2('c', '3');
  cs.append(c2);
  CPPUNIT_ASSERT(cs.thirdFromEnd() == cs.end());

  Coord c3('e', '5');
  cs.append(c3);
  CPPUNIT_ASSERT(cs.thirdFromEnd() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c1, *cs.thirdFromEnd());

  cs.append(Coord('g', '3'));
  CPPUNIT_ASSERT(cs.thirdFromEnd() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c2, *cs.thirdFromEnd());

  cs.append(c1);
  CPPUNIT_ASSERT(cs.thirdFromEnd() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c3, *cs.thirdFromEnd());
}

void CoordSequenceTests::secondFromEnd()
{
  CoordSequence cs;
  CPPUNIT_ASSERT(cs.secondFromEnd() == cs.end());

  Coord c1('e', '1');
  cs.append(c1);
  CPPUNIT_ASSERT(cs.secondFromEnd() == cs.end());

  Coord c2('c', '3');
  cs.append(c2);
  CPPUNIT_ASSERT(cs.secondFromEnd() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c1, *cs.secondFromEnd());

  cs.append(Coord('e', '5'));
  CPPUNIT_ASSERT(cs.secondFromEnd() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c2, *cs.secondFromEnd());
}

void CoordSequenceTests::last()
{
  CoordSequence cs;
  CPPUNIT_ASSERT(cs.last() == cs.end());

  Coord c1('e', '1');
  cs.append(c1);
  CPPUNIT_ASSERT(cs.last() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c1, *cs.last());

  Coord c2('c', '3');
  cs.append(c2);
  CPPUNIT_ASSERT(cs.last() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c2, *cs.last());

  Coord c3('e', '5');
  cs.append(c3);
  CPPUNIT_ASSERT(cs.last() != cs.end());
  CPPUNIT_ASSERT_EQUAL(c3, *cs.last());
}

void CoordSequenceTests::count()
{
  CoordSequence cs;
  CPPUNIT_ASSERT_EQUAL(0, cs.count());

  cs.append(Coord('a', '1'));
  CPPUNIT_ASSERT_EQUAL(1, cs.count());

  cs.append(Coord('c', '3'));
  CPPUNIT_ASSERT_EQUAL(2, cs.count());

  cs.append(Coord('e', '5'));
  CPPUNIT_ASSERT_EQUAL(3, cs.count());

  cs.append(Coord('g', '7'));
  CPPUNIT_ASSERT_EQUAL(4, cs.count());
}

void CoordSequenceTests::pop()
{
  CoordSequence cs;
  cs.append(Coord('a', '1'));
  cs.append(Coord('c', '3'));
  cs.append(Coord('e', '5'));
  cs.append(Coord('g', '7'));

  cs.pop();
  cs.pop();
  CPPUNIT_ASSERT_EQUAL(2, cs.count());

  CoordSequence testCs(Coord('a', '1'), Coord('c', '3'));
  CPPUNIT_ASSERT(cs == testCs);
}
