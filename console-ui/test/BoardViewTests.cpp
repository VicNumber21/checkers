#include "BoardViewTests.h"
#include "BoardView.h"
#include "Board.h"
#include "Draught.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;
using namespace Checkers::ConsoleUi;

CPPUNIT_TEST_SUITE_REGISTRATION( BoardViewTests );


void BoardViewTests::setUp()
{
}

void BoardViewTests::tearDown()
{
}

void BoardViewTests::emptyBoard()
{
  BoardView bV;
  std::string testString(
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                        );
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());

  bV.setRotation(BoardView::ERotation180);
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());
}

void BoardViewTests::rotation()
{
  Board b;
  BoardView bV(b);
  std::string testString(
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                        );
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());

  bV.setRotation(BoardView::ERotation180);
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());

  Draught d1(Coord('g','3'), Color::EBlack);
  b.put(d1);
  std::string testStringD1_R180(
                          "# # # # \n"
                          " # # # #\n"
                          "#b# # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                        );
  CPPUNIT_ASSERT_EQUAL(testStringD1_R180, bV.flushWhole());
  std::string testStringD1_R0(
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # #b#\n"
                          "# # # # \n"
                          " # # # #\n"
                        );
  bV.setRotation(BoardView::ERotation0);
  CPPUNIT_ASSERT_EQUAL(testStringD1_R0, bV.flushWhole());

  Board b2;
  bV.setBoard(b2);
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());

  bV.setRotation(BoardView::ERotation180);
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());

  Draught d2(Coord('f','6'), Color::EWhite, true);
  b2.put(d2);
  std::string testStringD2_R180(
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " #W# # #\n"
                          "# # # # \n"
                          " # # # #\n"
                        );
  CPPUNIT_ASSERT_EQUAL(testStringD2_R180, bV.flushWhole());
  std::string testStringD2_R0(
                          "# # # # \n"
                          " # # # #\n"
                          "# # #W# \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                        );
  bV.setRotation(BoardView::ERotation0);
  CPPUNIT_ASSERT_EQUAL(testStringD2_R0, bV.flushWhole());
}

void BoardViewTests::draughtChars()
{
  Board b;
  Draught d1(Coord('a','1'), Color::EBlack);
  Draught d2(Coord('c','1'), Color::EWhite);
  Draught d3(Coord('e','1'), Color::EBlack, true);
  Draught d4(Coord('g','1'), Color::EWhite, true);
  b.put(d1);
  b.put(d2);
  b.put(d3);
  b.put(d4);
  BoardView bV(b);
  std::string testString(
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          " # # # #\n"
                          "# # # # \n"
                          "b#w#B#W#\n"
                        );
  CPPUNIT_ASSERT_EQUAL(testString, bV.flushWhole());
}

void BoardViewTests::complexPosition()
{
  Board b;
  Draught d1(Coord('h','8'), Color::EBlack);
  Draught d2(Coord('g','5'), Color::EBlack);
  Draught d3(Coord('f','6'), Color::EBlack, true);
  Draught d4(Coord('d','4'), Color::EBlack, true);
  Draught d5(Coord('e','1'), Color::EBlack, true);
  Draught d6(Coord('a','3'), Color::EWhite);
  Draught d7(Coord('b','2'), Color::EWhite);
  Draught d8(Coord('c','5'), Color::EWhite, true);
  Draught d9(Coord('g','7'), Color::EWhite, true);
  b.put(d1);
  b.put(d2);
  b.put(d3);
  b.put(d4);
  b.put(d5);
  b.put(d6);
  b.put(d7);
  b.put(d8);
  b.put(d9);
  BoardView bV(b);
  std::string testString_R0(
                          "# # # #b\n"
                          " # # #W#\n"
                          "# # #B# \n"
                          " #W# #b#\n"
                          "# #B# # \n"
                          "w# # # #\n"
                          "#w# # # \n"
                          " # #B# #\n"
                        );
  CPPUNIT_ASSERT_EQUAL(testString_R0, bV.flushWhole());

  std::string testString_R180(
                          "# #B# # \n"
                          " # # #w#\n"
                          "# # # #w\n"
                          " # #B# #\n"
                          "#b# #W# \n"
                          " #B# # #\n"
                          "#W# # # \n"
                          "b# # # #\n"
                        );
  bV.setRotation(BoardView::ERotation180);
  CPPUNIT_ASSERT_EQUAL(testString_R180, bV.flushWhole());
}
