#include "CoordDeltaTests.h"
#include "RulesOfGameManager.h"
#include "RulesOfGameInstances.h"
#include "CoordDelta.h"
#include "Coord.h"
#include "PrettyPrint.h"

#include <vector>
#include <sstream>

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( CoordDeltaTests );

typedef std::vector<Coord> CoordV;
typedef std::vector<CoordDelta::Direction> DirectionV;

void CoordDeltaTests::setUp()
{
  RulesOfGameManager::instance().append(RulesOfGameInstanceInterface::Ptr(new AmericanCheckersRulesOfGame), true);
}

void CoordDeltaTests::tearDown()
{
  RulesOfGameManager::instance().reset();
}

DirectionV makeDirections()
{
  CoordDelta::Direction directions[] = {
              CoordDelta::ENorthWest
            , CoordDelta::ENorth
            , CoordDelta::ENorthEast
            , CoordDelta::EEast
            , CoordDelta::ESouthEast
            , CoordDelta::ESouth
            , CoordDelta::ESouthWest
            , CoordDelta::EWest
            };

  return DirectionV(directions, directions + sizeof(directions) / sizeof(CoordDelta::Direction));
}

std::vector<int> makeDeltasX1()
{
  int deltasX[] = {-1, 0, 1, 1, 1, 0, -1, -1};
  return std::vector<int>(deltasX, deltasX + sizeof(deltasX) / sizeof(int));
}

std::vector<int> makeDeltasY1()
{
  int deltasY[] = {1, 1, 1, 0, -1, -1, -1, 0};
  return std::vector<int>(deltasY, deltasY + sizeof(deltasY) / sizeof(int));
}

void CoordDeltaTests::deltaXY()
{
  CoordDelta delta(2, -4);
  CPPUNIT_ASSERT_EQUAL(2, delta.x());
  CPPUNIT_ASSERT_EQUAL(-4, delta.y());

  DirectionV directions = makeDirections();
  std::vector<int> expectedDeltaX = makeDeltasX1();
  std::vector<int> expectedDeltaY = makeDeltasY1();

  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedDeltaX.size());
  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedDeltaY.size());

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta2(directions[i], 1);

    std::stringstream ssx;
    ssx << "step " << i << " failed with x, test data: direction(" << std::hex << directions[i]  << "), " << delta2;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ssx.str().c_str(), expectedDeltaX[i], delta2.x());

    std::stringstream ssy;
    ssy << "step " << i << " failed with y, test data: direction(" << std::hex << directions[i]  << "), " << delta2;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ssy.str().c_str(), expectedDeltaY[i], delta2.y());
  }
}

std::vector<bool> makeHorizontal()
{
  bool values[] = {false, false, false, true, false, false, false, true};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

std::vector<bool> makeVertical()
{
  bool values[] = {false, true, false, false, false, true, false, false};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

std::vector<bool> makeDiagonal()
{
  bool values[] = {true, false, true, false, true, false, true, false};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

void CoordDeltaTests::geometryProperties()
{
  CoordDelta delta(0, 0);
  CPPUNIT_ASSERT(delta.isNull());

  DirectionV directions = makeDirections();
  std::vector<bool> expectedHorizontal = makeHorizontal();
  std::vector<bool> expectedVertical = makeVertical();
  std::vector<bool> expectedDiagonal = makeDiagonal();

  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedHorizontal.size());
  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedVertical.size());
  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedDiagonal.size());

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta2(directions[i], 1);

    std::stringstream ss;
    ss << "step " << i << " failed, test data: direction(" << std::hex << directions[i]  << "), " << delta2;
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), expectedHorizontal[i] == delta2.isHorizontal());
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), expectedVertical[i] == delta2.isVertical());
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), expectedDiagonal[i] == delta2.isDiagonal());
  }
}

void CoordDeltaTests::isSymmetric()
{
  CoordDelta delta1(2, 5);
  std::stringstream ss1;
  ss1 << delta1;
  CPPUNIT_ASSERT_MESSAGE(ss1.str().c_str() , !delta1.isSymmetric());

  CoordDelta delta2(-2, 2);
  std::stringstream ss2;
  ss2 << delta2;
  CPPUNIT_ASSERT_MESSAGE(ss2.str().c_str() , delta2.isSymmetric());

  CoordDelta delta3(CoordDelta::ENorth, 5);
  std::stringstream ss3;
  ss3 << delta3;
  CPPUNIT_ASSERT_MESSAGE(ss3.str().c_str() , delta3.isSymmetric());

  CoordDelta delta4(CoordDelta::ENorthEast, 3);
  std::stringstream ss4;
  ss4 << delta4;
  CPPUNIT_ASSERT_MESSAGE(ss4.str().c_str() , delta4.isSymmetric());

  CoordDelta delta5(CoordDelta::EWest, 4);
  std::stringstream ss5;
  ss5 << delta5;
  CPPUNIT_ASSERT_MESSAGE(ss5.str().c_str() , delta5.isSymmetric());
}

CoordV makeCoords()
{
  Coord coords[] = {
          Coord('a', '5')
        , Coord('c', '5')
        , Coord('e', '5')
        , Coord('e', '3')
        , Coord('e', '1')
        , Coord('c', '1')
        , Coord('a', '1')
        , Coord('a', '3')
        };

  return CoordV(coords, coords + sizeof(coords) / sizeof(Coord));
}

std::vector<bool> makeIsNorth()
{
  bool values[] = {true, true, true, false, false, false, false, false};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

std::vector<bool> makeIsSouth()
{
  bool values[] = {false, false, false, false, true, true, true, false};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

std::vector<bool> makeIsWest()
{
  bool values[] = {true, false, false, false, false, false, true, true};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

std::vector<bool> makeIsEast()
{
  bool values[] = {false, false, true, true, true, false, false, false};
  return std::vector<bool>(values, values + sizeof(values) / sizeof(bool));
}

void CoordDeltaTests::direction()
{
  DirectionV directions = makeDirections();
  std::vector<bool> isNorth = makeIsNorth();
  std::vector<bool> isSouth = makeIsSouth();
  std::vector<bool> isWest = makeIsWest();
  std::vector<bool> isEast = makeIsEast();

  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == isNorth.size());
  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == isSouth.size());
  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == isWest.size());
  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == isEast.size());

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta(directions[i], 1);

    std::stringstream ssx;
    ssx << "step " << i << " failed with x, test data: direction(" << std::hex << directions[i]  << "), " << delta;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ssx.str().c_str(), directions[i], delta.direction());
    CPPUNIT_ASSERT_MESSAGE(ssx.str().c_str(), isNorth[i] == delta.isNorth());
    CPPUNIT_ASSERT_MESSAGE(ssx.str().c_str(), isSouth[i] == delta.isSouth());
    CPPUNIT_ASSERT_MESSAGE(ssx.str().c_str(), isWest[i] == delta.isWest());
    CPPUNIT_ASSERT_MESSAGE(ssx.str().c_str(), isEast[i] == delta.isEast());
  }
}

void CoordDeltaTests::distance()
{
  CoordDelta delta1(2, 4);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be invalid for asymmetric delta", -1, delta1.distance());

  DirectionV directions = makeDirections();

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta(directions[i], 5);

    std::stringstream ssx;
    ssx << "step " << i << " failed with x, test data: direction(" << std::hex << directions[i]  << "), " << delta;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ssx.str().c_str(), 5, delta.distance());
  }
}

void CoordDeltaTests::CoordPlusDelta()
{
  Coord base('c', '3');

  DirectionV directions = makeDirections();
  CoordV expectedCoords = makeCoords();

  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedCoords.size());

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta(directions[i], 2);

    std::stringstream ss;
    ss << "step " << i << " failed, test data: direction(" << std::hex << directions[i]  << "), " << delta;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ss.str().c_str(), expectedCoords[i], base + delta);
  }
}

void CoordDeltaTests::CoordMinusDelta()
{
  Coord base('c', '3');

  DirectionV directions = makeDirections();
  CoordV expectedCoords = makeCoords();
  int count = expectedCoords.size();

  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == expectedCoords.size());

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta(directions[i], 2);

    std::stringstream ss;
    ss << "step " << i << " failed, test data: direction(" << std::hex << directions[i]  << "), " << delta;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ss.str().c_str(), expectedCoords[(i + 4) % count], base - delta);
  }
}

void CoordDeltaTests::CoordMinusCoord()
{
  Coord second('c', '3');

  DirectionV directions = makeDirections();
  CoordV firsts = makeCoords();

  CPPUNIT_ASSERT_MESSAGE("Wrong test data", directions.size() == firsts.size());

  for(unsigned int i = 0; i < directions.size(); ++i)
  {
    CoordDelta delta(directions[i], 2);

    std::stringstream ss;
    ss << "step " << i << " failed, test data: direction(" << std::hex << directions[i]  << "), " << delta;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(ss.str().c_str(), delta, firsts[i] - second);
  }
}
