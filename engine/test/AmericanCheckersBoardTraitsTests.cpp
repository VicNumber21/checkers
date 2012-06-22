#include "AmericanCheckersBoardTraitsTests.h"
#include "Coord.h"
#include "Color.h"

#include <algorithm>

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( AmericanCheckersBoardTraitsTests );


AmericanCheckersBoardTraitsTests::AmericanCheckersBoardTraitsTests()
  : m_board_height_width(8)
{
  const char rowNames[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  const char columnNames[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  CPPUNIT_ASSERT_EQUAL(m_board_height_width, (int)(sizeof(rowNames) / sizeof(char)));
  CPPUNIT_ASSERT_EQUAL(m_board_height_width, (int)(sizeof(columnNames) / sizeof(char)));

  m_row_names.assign(rowNames, rowNames + sizeof(rowNames) / sizeof(char));
  m_column_names.assign(columnNames, columnNames + sizeof(columnNames) / sizeof(char));
}

void AmericanCheckersBoardTraitsTests::setUp()
{
}

void AmericanCheckersBoardTraitsTests::tearDown()
{
}

void AmericanCheckersBoardTraitsTests::bounds()
{
  CPPUNIT_ASSERT_EQUAL(m_board_height_width, m_board_traits.height());
  CPPUNIT_ASSERT_EQUAL(m_board_height_width, m_board_traits.width());

  for(int i = 0; i < m_board_height_width; ++i)
  {
    CPPUNIT_ASSERT(m_board_traits.isRowInBound(i));
    CPPUNIT_ASSERT(m_board_traits.isRowInBound(m_row_names[i]));
    CPPUNIT_ASSERT(m_board_traits.isColumnInBound(i));
    CPPUNIT_ASSERT(m_board_traits.isColumnInBound(m_column_names[i]));
  }

  CPPUNIT_ASSERT(!m_board_traits.isRowInBound(-5));
  CPPUNIT_ASSERT(!m_board_traits.isRowInBound(10));
  CPPUNIT_ASSERT(!m_board_traits.isRowInBound('|'));

  CPPUNIT_ASSERT(!m_board_traits.isColumnInBound(-1));
  CPPUNIT_ASSERT(!m_board_traits.isColumnInBound(20));
  CPPUNIT_ASSERT(!m_board_traits.isColumnInBound('!'));
}

void AmericanCheckersBoardTraitsTests::nameIndexMap()
{
  for(int i = 0; i < m_board_height_width; ++i)
  {
    CPPUNIT_ASSERT_EQUAL(m_row_names[i], m_board_traits.rowName(i));
    CPPUNIT_ASSERT_EQUAL(m_column_names[i], m_board_traits.columnName(i));
    CPPUNIT_ASSERT_EQUAL(i, m_board_traits.rowIndex(m_row_names[i]));
    CPPUNIT_ASSERT_EQUAL(i, m_board_traits.columnIndex(m_column_names[i]));
  }

  CPPUNIT_ASSERT_EQUAL(m_board_traits.charOutOfBoundValue(), m_board_traits.rowName(-1));
  CPPUNIT_ASSERT_EQUAL(m_board_traits.charOutOfBoundValue(), m_board_traits.rowName(8));
  CPPUNIT_ASSERT_EQUAL(m_board_traits.charOutOfBoundValue(), m_board_traits.columnName(-1));
  CPPUNIT_ASSERT_EQUAL(m_board_traits.charOutOfBoundValue(), m_board_traits.columnName(8));

  CPPUNIT_ASSERT_EQUAL(m_board_traits.intOutOfBoundValue(), m_board_traits.rowIndex('A'));
  CPPUNIT_ASSERT_EQUAL(m_board_traits.intOutOfBoundValue(), m_board_traits.columnIndex('1'));
}

void AmericanCheckersBoardTraitsTests::kingRow()
{
  CPPUNIT_ASSERT(!m_board_traits.canPutManOnKingRow());

  CPPUNIT_ASSERT(m_board_traits.isKingRow(0, Color::EWhite));
  CPPUNIT_ASSERT(m_board_traits.isKingRow('1', Color::EWhite));

  for(int i = 1; i < m_board_height_width; ++i)
  {
    CPPUNIT_ASSERT(!m_board_traits.isKingRow(i, Color::EWhite));
    CPPUNIT_ASSERT(!m_board_traits.isKingRow(m_row_names[i], Color::EWhite));
  }

  CPPUNIT_ASSERT(m_board_traits.isKingRow(7, Color::EBlack));
  CPPUNIT_ASSERT(m_board_traits.isKingRow('8', Color::EBlack));

  for(int i = 0; i < m_board_height_width - 1; ++i)
  {
    CPPUNIT_ASSERT(!m_board_traits.isKingRow(i, Color::EBlack));
    CPPUNIT_ASSERT(!m_board_traits.isKingRow(m_row_names[i], Color::EBlack));
  }
}

void AmericanCheckersBoardTraitsTests::squareColor()
{
  int halfOfSquaresCount = m_board_height_width * m_board_height_width / 2;
  for(int i = 0; i < halfOfSquaresCount; ++i)
  {
    int row = i / 4;
    int colBlack = (i % 4) * 2;
    int colWhite = colBlack + 1;

    if(row % 2 == 1)
      std::swap(colBlack, colWhite);

    CPPUNIT_ASSERT(m_board_traits.isBlackSquare(Coord(colBlack, row)));
    CPPUNIT_ASSERT(m_board_traits.isWhiteSquare(Coord(colWhite, row)));
  }
}
