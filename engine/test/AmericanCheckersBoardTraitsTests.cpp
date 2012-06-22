#include "AmericanCheckersBoardTraitsTests.h"
#include "AmericanCheckersBoardTraits.h"
#include "Coord.h"
#include "Color.h"

#include <algorithm>

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( AmericanCheckersBoardTraitsTests );


void AmericanCheckersBoardTraitsTests::setUp()
{
}

void AmericanCheckersBoardTraitsTests::tearDown()
{
}

void AmericanCheckersBoardTraitsTests::bounds()
{
  AmericanCheckersBoardTraits boardTraits;
  CPPUNIT_ASSERT_EQUAL(8, boardTraits.height());
  CPPUNIT_ASSERT_EQUAL(8, boardTraits.width());

  const int count = 8;
  const char rowNames[count] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  const char columnNames[count] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  for(int i = 0; i < count; ++i)
  {
    CPPUNIT_ASSERT(boardTraits.isLineInBound(i));
    CPPUNIT_ASSERT(boardTraits.isLineInBound(rowNames[i]));
    CPPUNIT_ASSERT(boardTraits.isColumnInBound(i));
    CPPUNIT_ASSERT(boardTraits.isColumnInBound(columnNames[i]));
  }

  CPPUNIT_ASSERT(!boardTraits.isLineInBound(-5));
  CPPUNIT_ASSERT(!boardTraits.isLineInBound(10));
  CPPUNIT_ASSERT(!boardTraits.isLineInBound('|'));

  CPPUNIT_ASSERT(!boardTraits.isColumnInBound(-1));
  CPPUNIT_ASSERT(!boardTraits.isColumnInBound(20));
  CPPUNIT_ASSERT(!boardTraits.isColumnInBound('!'));
}

void AmericanCheckersBoardTraitsTests::nameIndexMap()
{
  const int count = 8;
  const char rowNames[count] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  const char columnNames[count] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  AmericanCheckersBoardTraits boardTraits;

  for(int i = 0; i < count; ++i)
  {
    CPPUNIT_ASSERT_EQUAL(rowNames[i], boardTraits.lineName(i));
    CPPUNIT_ASSERT_EQUAL(columnNames[i], boardTraits.columnName(i));
    CPPUNIT_ASSERT_EQUAL(i, boardTraits.lineIndex(rowNames[i]));
    CPPUNIT_ASSERT_EQUAL(i, boardTraits.columnIndex(columnNames[i]));
  }

  CPPUNIT_ASSERT_EQUAL(boardTraits.charOutOfBoundValue(), boardTraits.lineName(-1));
  CPPUNIT_ASSERT_EQUAL(boardTraits.charOutOfBoundValue(), boardTraits.lineName(8));
  CPPUNIT_ASSERT_EQUAL(boardTraits.charOutOfBoundValue(), boardTraits.columnName(-1));
  CPPUNIT_ASSERT_EQUAL(boardTraits.charOutOfBoundValue(), boardTraits.columnName(8));

  CPPUNIT_ASSERT_EQUAL(boardTraits.intOutOfBoundValue(), boardTraits.lineIndex('A'));
  CPPUNIT_ASSERT_EQUAL(boardTraits.intOutOfBoundValue(), boardTraits.columnIndex('1'));
}

void AmericanCheckersBoardTraitsTests::kingLine()
{
  AmericanCheckersBoardTraits boardTraits;
  CPPUNIT_ASSERT(boardTraits.isKingLine(0, Color::EWhite));
  CPPUNIT_ASSERT(boardTraits.isKingLine('1', Color::EWhite));
  CPPUNIT_ASSERT(boardTraits.isKingLine(7, Color::EBlack));
  CPPUNIT_ASSERT(boardTraits.isKingLine('8', Color::EBlack));
}

void AmericanCheckersBoardTraitsTests::squareColor()
{
  AmericanCheckersBoardTraits boardTraits;

  for(int i = 0; i < 32; ++i)
  {
    int row = i / 4;
    int colBlack = (i % 4) * 2;
    int colWhite = colBlack + 1;

    if(row % 2 == 1)
      std::swap(colBlack, colWhite);

    CPPUNIT_ASSERT(boardTraits.isBlackSquare(Coord(colBlack, row)));
    CPPUNIT_ASSERT(boardTraits.isWhiteSquare(Coord(colWhite, row)));
  }
}
