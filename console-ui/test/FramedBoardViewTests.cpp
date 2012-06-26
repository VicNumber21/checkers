#include "FramedBoardViewTests.h"
#include "RulesOfGameManager.h"
#include "RulesOfGameInstances.h"
#include "FramedBoardView.h"
#include "Board.h"
#include "Draught.h"
#include "Coord.h"
#include "Color.h"

using namespace Checkers::Engine;
using namespace Checkers::ConsoleUi;

CPPUNIT_TEST_SUITE_REGISTRATION( FramedBoardViewTests );


std::string& replace_space_by_dot(std::string& aStr)
{
  for(std::string::iterator it = aStr.begin(); it != aStr.end(); ++it)
  {
    if(*it == ' ')
      *it = '.';
  }
  return aStr;
}

void FramedBoardViewTests::setUp()
{
  RulesOfGameManager::instance().append(RulesOfGameInstanceInterface::Ptr(new AmericanCheckersRulesOfGame), true);
}

void FramedBoardViewTests::tearDown()
{
  RulesOfGameManager::instance().reset();
}

void FramedBoardViewTests::emptyBoard()
{
  FramedBoardView bV;
  std::string testString_R0(
                          "  ABCDEFGH  \n"
                          " +--------+ \n"
                          "8|# # # # |8\n"
                          "7| # # # #|7\n"
                          "6|# # # # |6\n"
                          "5| # # # #|5\n"
                          "4|# # # # |4\n"
                          "3| # # # #|3\n"
                          "2|# # # # |2\n"
                          "1| # # # #|1\n"
                          " +--------+ \n"
                          "  ABCDEFGH  \n"
                        );
  std::string tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testString_R0), replace_space_by_dot(tmpRes));

  bV.setRotation(BoardView::ERotation180);
  std::string testString_R180(
                          "  HGFEDCBA  \n"
                          " +--------+ \n"
                          "1|# # # # |1\n"
                          "2| # # # #|2\n"
                          "3|# # # # |3\n"
                          "4| # # # #|4\n"
                          "5|# # # # |5\n"
                          "6| # # # #|6\n"
                          "7|# # # # |7\n"
                          "8| # # # #|8\n"
                          " +--------+ \n"
                          "  HGFEDCBA  \n"
                        );
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testString_R180), replace_space_by_dot(tmpRes)); 
}

void FramedBoardViewTests::rotation()
{
  Board b;
  FramedBoardView bV(b);
  std::string testString_R0(
                          "  ABCDEFGH  \n"
                          " +--------+ \n"
                          "8|# # # # |8\n"
                          "7| # # # #|7\n"
                          "6|# # # # |6\n"
                          "5| # # # #|5\n"
                          "4|# # # # |4\n"
                          "3| # # # #|3\n"
                          "2|# # # # |2\n"
                          "1| # # # #|1\n"
                          " +--------+ \n"
                          "  ABCDEFGH  \n"
                        );
  std::string tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testString_R0), replace_space_by_dot(tmpRes));

  bV.setRotation(BoardView::ERotation180);
  std::string testString_R180(
                          "  HGFEDCBA  \n"
                          " +--------+ \n"
                          "1|# # # # |1\n"
                          "2| # # # #|2\n"
                          "3|# # # # |3\n"
                          "4| # # # #|4\n"
                          "5|# # # # |5\n"
                          "6| # # # #|6\n"
                          "7|# # # # |7\n"
                          "8| # # # #|8\n"
                          " +--------+ \n"
                          "  HGFEDCBA  \n"
                        );
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testString_R180), replace_space_by_dot(tmpRes));

  Draught d1(Coord('g','3'), Color::EBlack);
  b.put(d1);
  std::string testStringD1_R180(
                          "  HGFEDCBA  \n"
                          " +--------+ \n"
                          "1|# # # # |1\n"
                          "2| # # # #|2\n"
                          "3|#b# # # |3\n"
                          "4| # # # #|4\n"
                          "5|# # # # |5\n"
                          "6| # # # #|6\n"
                          "7|# # # # |7\n"
                          "8| # # # #|8\n"
                          " +--------+ \n"
                          "  HGFEDCBA  \n"
                        );
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testStringD1_R180), replace_space_by_dot(tmpRes));

  bV.setRotation(BoardView::ERotation0);
  std::string testStringD1_R0(
                          "  ABCDEFGH  \n"
                          " +--------+ \n"
                          "8|# # # # |8\n"
                          "7| # # # #|7\n"
                          "6|# # # # |6\n"
                          "5| # # # #|5\n"
                          "4|# # # # |4\n"
                          "3| # # #b#|3\n"
                          "2|# # # # |2\n"
                          "1| # # # #|1\n"
                          " +--------+ \n"
                          "  ABCDEFGH  \n"
                        );
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testStringD1_R0), replace_space_by_dot(tmpRes));

  Board b2;
  bV.setBoard(b2);
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testString_R0), replace_space_by_dot(tmpRes));

  bV.setRotation(BoardView::ERotation180);
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testString_R180), replace_space_by_dot(tmpRes));

  Draught d2(Coord('f','6'), Color::EWhite, true);
  b2.put(d2);
  std::string testStringD2_R180(
                          "  HGFEDCBA  \n"
                          " +--------+ \n"
                          "1|# # # # |1\n"
                          "2| # # # #|2\n"
                          "3|# # # # |3\n"
                          "4| # # # #|4\n"
                          "5|# # # # |5\n"
                          "6| #W# # #|6\n"
                          "7|# # # # |7\n"
                          "8| # # # #|8\n"
                          " +--------+ \n"
                          "  HGFEDCBA  \n"
                        );
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testStringD2_R180), replace_space_by_dot(tmpRes));

  bV.setRotation(BoardView::ERotation0);
  std::string testStringD2_R0(
                          "  ABCDEFGH  \n"
                          " +--------+ \n"
                          "8|# # # # |8\n"
                          "7| # # # #|7\n"
                          "6|# # #W# |6\n"
                          "5| # # # #|5\n"
                          "4|# # # # |4\n"
                          "3| # # # #|3\n"
                          "2|# # # # |2\n"
                          "1| # # # #|1\n"
                          " +--------+ \n"
                          "  ABCDEFGH  \n"
                        );
  tmpRes = bV.flushWhole();
  CPPUNIT_ASSERT_EQUAL(replace_space_by_dot(testStringD2_R0), replace_space_by_dot(tmpRes));
}
