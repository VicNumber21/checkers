#include "AmericanCheckersPositionAnalyserTests.h"
#include "AmericanCheckersPositionAnalyser.h"
#include "Move.h"
#include "CoordSequence.h"
#include "Board.h"
#include "Draught.h"
#include "Color.h"
#include "Coord.h"
#include "RulesOfGame.h"
#include "PrettyPrint.h"

#include <list>
#include <sstream>

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( AmericanCheckersPositionAnalyserTests );

typedef std::list<Board> BoardList;
typedef std::list<Coord> CoordList;
typedef std::list<CoordList> CoordLists;


void AmericanCheckersPositionAnalyserTests::setUp()
{
}

void AmericanCheckersPositionAnalyserTests::tearDown()
{
}

void batchMove(BoardList &aBoards, const CoordList &aFrom, const CoordList &aTo)
{
  CPPUNIT_ASSERT_EQUAL(aBoards.size(), aFrom.size());
  CPPUNIT_ASSERT_EQUAL(aBoards.size(), aTo.size());

  BoardList::iterator boardIt = aBoards.begin();
  CoordList::const_iterator fromIt = aFrom.begin();
  CoordList::const_iterator toIt = aTo.begin();
  for(; boardIt != aBoards.end(); ++boardIt, ++fromIt, ++toIt)
  {
    std::stringstream ss;
    ss << *boardIt << *fromIt << *toIt;

    Maybe<Draught> d = boardIt->takeDraught(*fromIt);
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), !d.isNothing());
    d().moveTo(*toIt);
    if(RulesOfGame::BoardBounds::isKingRow(toIt->y(), d().color()))
      d().makeKing();
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), boardIt->put(d()));
  }
}

void batchRemove(Board &aBoard, const CoordList &aRemove)
{
  CoordList::const_iterator removeIt = aRemove.begin();
  for(; removeIt != aRemove.end(); ++removeIt)
  {
    std::stringstream ss;
    ss << aBoard << *removeIt;

    Maybe<Draught> d = aBoard.takeDraught(*removeIt);
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), !d.isNothing());
  }
}

void batchRemove(BoardList &aBoards, const CoordLists &aRemove)
{
  CPPUNIT_ASSERT_EQUAL(aBoards.size(), aRemove.size());

  BoardList::iterator boardIt = aBoards.begin();
  CoordLists::const_iterator removeIt = aRemove.begin();
  for(; boardIt != aBoards.end(); ++boardIt, ++removeIt)
  {
    batchRemove(*boardIt, *removeIt);
  }
}

void validateMoveList(const PositionAnalyser::MoveList &aMoveList, const Board &aFrom, const BoardList &aTo)
{
  BoardList expectedTo(aTo);

  for(PositionAnalyser::MoveList::const_iterator it = aMoveList.begin(); it != aMoveList.end(); ++it)
  {
    CPPUNIT_ASSERT_EQUAL(aFrom, it->from());
    int sizeBefore = expectedTo.size();
    expectedTo.remove(it->to());

    std::stringstream ss;
    ss << it->to();
    CPPUNIT_ASSERT_MESSAGE(ss.str().c_str(), (--sizeBefore) == expectedTo.size());
  }

  CPPUNIT_ASSERT_EQUAL(0, (int)expectedTo.size());
}

void AmericanCheckersPositionAnalyserTests::validMovesSimple()
{
  const Coord cBlackC3('c', '3');
  const Coord cBlackKingD4('d', '4');
  const Coord cBlackG3('g', '3');
  const Coord cBlackKingB6('b', '6');

  const Coord cWhiteE5('e', '5');
  const Coord cWhiteF6('f', '6');

  const Coord cMoveToA7('a', '7');
  const Coord cMoveToC7('c', '7');
  const Coord cMoveToA5('a', '5');
  const Coord cMoveToC5('c', '5');
  const Coord cMoveToE3('e', '3');
  const Coord cMoveToB4('b', '4');
  const Coord cMoveToF4('f', '4');
  const Coord cMoveToH4('h', '4');

  const int expectedMoveCount = 9;

  Board b;
  b.put(Draught(cBlackC3, Color::EBlack));
  b.put(Draught(cBlackG3, Color::EBlack));
  b.put(Draught(cBlackKingD4, Color::EBlack, true));
  b.put(Draught(cBlackKingB6, Color::EBlack, true));
  b.put(Draught(cWhiteE5, Color::EWhite));
  b.put(Draught(cWhiteF6, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b, Color::EBlack);

  CPPUNIT_ASSERT_EQUAL(expectedMoveCount, (int)analyser.validMoves().size());

  BoardList toB(expectedMoveCount, b);

  Coord tempFrom[expectedMoveCount] = {cBlackKingB6, cBlackKingB6, cBlackKingB6, cBlackKingB6, cBlackKingD4, cBlackKingD4, cBlackC3, cBlackG3, cBlackG3};
  CoordList from(tempFrom, tempFrom + expectedMoveCount);

  Coord tempTo[expectedMoveCount] = {cMoveToA7, cMoveToC7, cMoveToA5, cMoveToC5, cMoveToC5, cMoveToE3, cMoveToB4, cMoveToF4, cMoveToH4};
  CoordList to(tempTo, tempTo + expectedMoveCount);

  batchMove(toB, from, to);

  validateMoveList(analyser.validMoves(), b, toB);
}

void AmericanCheckersPositionAnalyserTests::validMovesJump()
{
  const Coord cBlackB6('b', '6');
  const Coord cBlackB4('b', '4');
  const Coord cBlackKingB2('b', '2');
  const Coord cBlackKingD4('d', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackKingF6('f', '6');
  const Coord cBlackF2('f', '2');

  const Coord cWhiteC5('c', '5');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteKingE5('e', '5');

  const Coord cMoveToC1('c', '1');
  const Coord cMoveToG1('g', '1');
  const Coord cMoveToG5('g', '5');
  const Coord cMoveToG7('g', '7');
  const Coord cMoveToA1('a', '1');
  const Coord cMoveToG3('g', '3');
  const Coord cMoveToC7('c', '7');

  const int expectedMoveCount = 8;

  Board b;
  b.put(Draught(cBlackB6, Color::EBlack));
  b.put(Draught(cBlackB4, Color::EBlack));
  b.put(Draught(cBlackKingB2, Color::EBlack, true));
  b.put(Draught(cBlackKingD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackKingF6, Color::EBlack, true));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteKingE5, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b, Color::EWhite);

  CPPUNIT_ASSERT_EQUAL(expectedMoveCount, (int)analyser.validMoves().size());

  BoardList toB(expectedMoveCount, b);

  Coord tempFrom[expectedMoveCount] = {cWhiteC5, cWhiteC5, cWhiteC5, cWhiteE7, cWhiteKingE5, cWhiteKingE5, cWhiteKingE5, cWhiteKingE5};
  CoordList from(tempFrom, tempFrom + expectedMoveCount);

  Coord tempTo[expectedMoveCount] = {cMoveToC1, cMoveToC1, cMoveToG1, cMoveToG5, cMoveToG7, cMoveToA1, cMoveToG3, cMoveToC7};
  CoordList to(tempTo, tempTo + expectedMoveCount);

  batchMove(toB, from, to);

  CoordLists remove;
  Coord tempRemove0[] = {cBlackB4, cBlackKingB2};
  remove.push_back(CoordList(tempRemove0, tempRemove0 + sizeof(tempRemove0) / sizeof(Coord)));
  Coord tempRemove1[] = {cBlackKingD4, cBlackD2};
  remove.push_back(CoordList(tempRemove1, tempRemove1 + sizeof(tempRemove1) / sizeof(Coord)));
  Coord tempRemove2[] = {cBlackKingD4, cBlackF2};
  remove.push_back(CoordList(tempRemove2, tempRemove2 + sizeof(tempRemove2) / sizeof(Coord)));
  Coord tempRemove3[] = {cBlackKingF6};
  remove.push_back(CoordList(tempRemove3, tempRemove3 + sizeof(tempRemove3) / sizeof(Coord)));
  Coord tempRemove4[] = {cBlackKingF6};
  remove.push_back(CoordList(tempRemove4, tempRemove4 + sizeof(tempRemove4) / sizeof(Coord)));
  Coord tempRemove5[] = {cBlackKingD4, cBlackKingB2};
  remove.push_back(CoordList(tempRemove5, tempRemove5 + sizeof(tempRemove5) / sizeof(Coord)));
  Coord tempRemove6[] = {cBlackKingD4, cBlackD2, cBlackF2};
  remove.push_back(CoordList(tempRemove6, tempRemove6 + sizeof(tempRemove6) / sizeof(Coord)));
  Coord tempRemove7[] = {cBlackKingD4, cBlackB4, cBlackB6};
  remove.push_back(CoordList(tempRemove7, tempRemove7 + sizeof(tempRemove7) / sizeof(Coord)));

  batchRemove(toB, remove);

  validateMoveList(analyser.validMoves(), b, toB);
}

void AmericanCheckersPositionAnalyserTests::validMovesNoMoves()
{
  Board bEmpty;
  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(bEmpty, Color::EWhite);
  CPPUNIT_ASSERT_EQUAL(0, (int)analyser.validMoves().size());

  analyser.setPosition(bEmpty, Color::EBlack);
  CPPUNIT_ASSERT_EQUAL(0, (int)analyser.validMoves().size());

  Board b;
  b.put(Draught(Coord('h', '6'), Color::EBlack));
  b.put(Draught(Coord('g', '7'), Color::EWhite));
  b.put(Draught(Coord('f', '8'), Color::EWhite));

  analyser.setPosition(b, Color::EBlack);
  CPPUNIT_ASSERT_EQUAL(0, (int)analyser.validMoves().size());
}

void AmericanCheckersPositionAnalyserTests::createMoveIncompleteCoordSequence()
{
  const Coord cBlackStart('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);

  Move m = analyser.createMove(CoordSequence());
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorIncompleteCoordSequence);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMove()
{
  const Coord cBlackStart('c', '3');
  const Coord cBlackLeftForward('b', '4');
  const Coord cBlackRightForward('d', '4');

  const Coord cWhiteStart('f', '6');
  const Coord cWhiteLeftForward('g', '5');
  const Coord cWhiteRightForward('e', '5');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveByKing()
{
  const Coord cBlackStart('c', '3');
  const Coord cBlackLeftForward('b', '4');
  const Coord cBlackRightForward('d', '4');
  const Coord cBlackLeftBack('b', '2');
  const Coord cBlackRightBack('d', '2');

  const Coord cWhiteStart('f', '6');
  const Coord cWhiteLeftForward('g', '5');
  const Coord cWhiteRightForward('e', '5');
  const Coord cWhiteLeftBack('g', '7');
  const Coord cWhiteRightBack('e', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csBlackLeftBack(cBlackStart, cBlackLeftBack);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, m.to());

  CoordSequence csBlackRightBack(cBlackStart, cBlackRightBack);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  m = analyser.createMove(csBlackRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());

  CoordSequence csWhiteRightBack(cWhiteStart, cWhiteRightBack);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, m.to());

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveGetKing()
{
  const Coord cBlackStart('c', '7');
  const Coord cBlackLeftForward('b', '8');
  const Coord cBlackRightForward('d', '8');

  const Coord cWhiteStart('f', '2');
  const Coord cWhiteLeftForward('g', '1');
  const Coord cWhiteRightForward('e', '1');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveNoRequestedDraught()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackWrongStart('e', '5');
  const Coord cBlackMoveTo('d', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlack(cBlackWrongStart, cBlackMoveTo);
  m = analyser.createMove(csBlack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorNoRequestedDraught);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveInWrongDirection()
{
  const Coord cBlackStart('c', '7');
  const Coord cBlackLeftBack('b', '6');
  const Coord cBlackRightBack('d', '6');

  const Coord cWhiteStart('f', '2');
  const Coord cWhiteLeftBack('g', '3');
  const Coord cWhiteRightBack('e', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftBack(cBlackStart, cBlackLeftBack);
  m = analyser.createMove(csBlackLeftBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csBlackRightBack(cBlackStart, cBlackRightBack);
  m = analyser.createMove(csBlackRightBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csWhiteRightBack(cWhiteStart, cWhiteRightBack);
  m = analyser.createMove(csWhiteRightBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveToBusySquare()
{
  const Coord cBlackStart('d', '4');
  const Coord cBlackLeftForward('c', '5');

  const Coord cWhiteStart('e', '5');
  const Coord cWhiteLeftForward('f', '4');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cBlackLeftForward, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cWhiteLeftForward, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csBlackRightForward(cBlackStart, cWhiteStart);
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteRightForward(cWhiteStart, cBlackStart);
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createSimpleMoveJumpExist()
{
  const Coord cBlackStart('d', '4');
  const Coord cBlackLeftForward('c', '5');

  const Coord cWhiteStart('e', '5');
  const Coord cWhiteLeftForward('f', '4');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJump()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack('f', '4');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite('c', '5');
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteRightForward('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cAnotherBlack, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpByKing()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack1('f', '4');
  const Coord cAnotherBlack2('f', '6');
  const Coord cAnotherBlack3('d', '6');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackLeftBack('b', '2');
  const Coord cBlackRightBack('f', '2');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite1('c', '5');
  const Coord cAnotherWhite2('c', '3');
  const Coord cAnotherWhite3('e', '3');
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteLeftBack('g', '7');
  const Coord cWhiteRightBack('c', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack, true));
  b.put(Draught(cAnotherBlack1, Color::EBlack));
  b.put(Draught(cAnotherBlack2, Color::EBlack, true));
  b.put(Draught(cAnotherBlack3, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cAnotherWhite1, Color::EWhite));
  b.put(Draught(cAnotherWhite2, Color::EWhite));
  b.put(Draught(cAnotherWhite3, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackLeftBack(cBlackStart, cBlackLeftBack);
  Board bAfterBlackLeftBack;
  bAfterBlackLeftBack.put(Draught(cBlackLeftBack, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackLeftBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackLeftBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterBlackLeftBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csBlackLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftBack, m.to());

  CoordSequence csBlackRightBack(cBlackStart, cBlackRightBack);
  Board bAfterBlackRightBack;
  bAfterBlackRightBack.put(Draught(cBlackRightBack, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackRightBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackRightBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterBlackRightBack.put(Draught(cWhiteStart, Color::EWhite, true));
  bAfterBlackRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterBlackRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csBlackRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightBack, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());

  CoordSequence csWhiteRightBack(cWhiteStart, cWhiteRightBack);
  Board bAfterWhiteRightBack;
  bAfterWhiteRightBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteRightBack.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteRightBack.put(Draught(cWhiteRightBack, Color::EWhite, true));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteRightBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csWhiteRightBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightBack, m.to());

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  Board bAfterWhiteLeftBack;
  bAfterWhiteLeftBack.put(Draught(cBlackStart, Color::EBlack, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftBack.put(Draught(cAnotherBlack3, Color::EBlack));
  bAfterWhiteLeftBack.put(Draught(cWhiteLeftBack, Color::EWhite, true));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite1, Color::EWhite));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite2, Color::EWhite));
  bAfterWhiteLeftBack.put(Draught(cAnotherWhite3, Color::EWhite, true));
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftBack, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpGetKing()
{
  const Coord cBlackStart('d', '6');
  const Coord cAnotherBlack1('d', '2');
  const Coord cAnotherBlack2('f', '2');
  const Coord cBlackLeftForward('b', '8');
  const Coord cBlackRightForward('f', '8');

  const Coord cWhiteStart('e', '3');
  const Coord cAnotherWhite1('c', '7');
  const Coord cAnotherWhite2('e', '7');
  const Coord cWhiteLeftForward('g', '1');
  const Coord cWhiteRightForward('c', '1');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack1, Color::EBlack));
  b.put(Draught(cAnotherBlack2, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite1, Color::EWhite, true));
  b.put(Draught(cAnotherWhite2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  Board bAfterBlackLeftForward;
  bAfterBlackLeftForward.put(Draught(cBlackLeftForward, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackLeftForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackLeftForward, m.to());

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  Board bAfterBlackRightForward;
  bAfterBlackRightForward.put(Draught(cBlackRightForward, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterBlackRightForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterBlackRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bAfterBlackRightForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterBlackRightForward, m.to());

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  Board bAfterWhiteRightForward;
  bAfterWhiteRightForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteRightForward.put(Draught(cAnotherBlack2, Color::EBlack, true));
  bAfterWhiteRightForward.put(Draught(cWhiteRightForward, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  bAfterWhiteRightForward.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteRightForward, m.to());

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  Board bAfterWhiteLeftForward;
  bAfterWhiteLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bAfterWhiteLeftForward.put(Draught(cWhiteLeftForward, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite1, Color::EWhite, true));
  bAfterWhiteLeftForward.put(Draught(cAnotherWhite2, Color::EWhite));
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bAfterWhiteLeftForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpNoRequestedDraught()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackWrongStart('g', '5');
  const Coord cBlackMoveTo('e', '7');

  const Coord cWhite1('d', '6');
  const Coord cWhite2('f', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cWhite1, Color::EWhite));
  b.put(Draught(cWhite1, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlack(cBlackWrongStart, cBlackMoveTo);
  m = analyser.createMove(csBlack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorNoRequestedDraught);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpNothingToJumpOver()
{
  const Coord cBlackStart('c', '5');
  const Coord cBlackMoveTo('e', '7');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlack(cBlackStart, cBlackMoveTo);
  m = analyser.createMove(csBlack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorNothingToJumpOver);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpInWrongDirection()
{
  const Coord cBlackStart('c', '5');
  const Coord cAnotherBlack('e', '5');
  const Coord cBlackLeftBack('a', '3');
  const Coord cBlackRightBack('e', '3');

  const Coord cWhiteStart('d', '4');
  const Coord cAnotherWhite('b', '4');
  const Coord cWhiteLeftBack('b', '6');
  const Coord cWhiteRightBack('f', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack, true));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftBack(cBlackStart, cBlackLeftBack);
  m = analyser.createMove(csBlackLeftBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csBlackRightBack(cBlackStart, cBlackRightBack);
  m = analyser.createMove(csBlackRightBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csWhiteRightBack(cWhiteStart, cWhiteRightBack);
  m = analyser.createMove(csWhiteRightBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpToBusySquare()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack1('f', '4');
  const Coord cAnotherBlack2('e', '3');
  const Coord cBlackLeftForward('b', '6');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite1('c', '5');
  const Coord cAnotherWhite2('d', '6');
  const Coord cWhiteLeftForward('g', '3');
  const Coord cWhiteRightForward('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack1, Color::EBlack, true));
  b.put(Draught(cAnotherBlack2, Color::EBlack));
  b.put(Draught(cBlackLeftForward, Color::EWhite, true));
  b.put(Draught(cBlackRightForward, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite1, Color::EWhite));
  b.put(Draught(cAnotherWhite2, Color::EWhite));
  b.put(Draught(cWhiteLeftForward, Color::EBlack));
  b.put(Draught(cWhiteRightForward, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackLeftForward(cBlackStart, cBlackLeftForward);
  m = analyser.createMove(csBlackLeftForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteLeftForward(cWhiteStart, cWhiteLeftForward);
  m = analyser.createMove(csWhiteLeftForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpMoreJumpExist()
{
  const Coord cBlackStart('d', '4');
  const Coord cAnotherBlack('b', '4');
  const Coord cBlackRightForward('f', '6');

  const Coord cWhiteStart('e', '5');
  const Coord cAnotherWhite('g', '7');
  const Coord cWhiteRightForward('c', '3');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csWhiteRightForward(cWhiteStart, cWhiteRightForward);
  m = analyser.createMove(csWhiteRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);
}

void AmericanCheckersPositionAnalyserTests::createSimpleJumpOverSameColor()
{
  const Coord cBlackStart('b', '4');
  const Coord cAnotherBlack('c', '5');
  const Coord cBlackRightForward('d', '6');

  const Coord cWhiteStart('f', '4');
  const Coord cAnotherWhite('g', '5');
  const Coord cWhiteLeftBack('h', '6');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite, true));
  b.put(Draught(cAnotherWhite, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackRightForward(cBlackStart, cBlackRightForward);
  m = analyser.createMove(csBlackRightForward);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpOverSameColor);

  CoordSequence csWhiteLeftBack(cWhiteStart, cWhiteLeftBack);
  m = analyser.createMove(csWhiteLeftBack);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpOverSameColor);
}

void AmericanCheckersPositionAnalyserTests::createComplexJump()
{
  const Coord cBlackStart('c', '1');
  const Coord cAnotherBlack1('e', '3');
  const Coord cAnotherBlack2('g', '3');
  const Coord cAnotherBlack3('g', '5');
  const Coord cAnotherBlack4('g', '7');
  const Coord cBlackJump1('a', '3');
  const Coord cBlackJump2('c', '5');
  const Coord cBlackJump3LeftForward('a', '7');
  const Coord cBlackJump3RightForward('e', '7');

  const Coord cWhiteStart('f', '8');
  const Coord cAnotherWhite1('b', '6');
  const Coord cAnotherWhite2('d', '6');
  const Coord cAnotherWhite3('b', '4');
  const Coord cAnotherWhite4('b', '2');
  const Coord cWhiteJump1('h', '6');
  const Coord cWhiteJump2('f', '4');
  const Coord cWhiteJump3LeftForward('h', '2');
  const Coord cWhiteJump3RightForward('d', '2');

  Board b;
  b.put(Draught(cBlackStart, Color::EBlack));
  b.put(Draught(cAnotherBlack1, Color::EBlack));
  b.put(Draught(cAnotherBlack2, Color::EBlack));
  b.put(Draught(cAnotherBlack3, Color::EBlack, true));
  b.put(Draught(cAnotherBlack4, Color::EBlack));
  b.put(Draught(cWhiteStart, Color::EWhite));
  b.put(Draught(cAnotherWhite1, Color::EWhite));
  b.put(Draught(cAnotherWhite2, Color::EWhite, true));
  b.put(Draught(cAnotherWhite3, Color::EWhite));
  b.put(Draught(cAnotherWhite4, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackAtTheEndLeftForward(cBlackStart, cBlackJump1);
  csBlackAtTheEndLeftForward.append(cBlackJump2);
  CoordSequence csBlackAtTheEndRightForward(csBlackAtTheEndLeftForward);
  csBlackAtTheEndLeftForward.append(cBlackJump3LeftForward);
  csBlackAtTheEndRightForward.append(cBlackJump3RightForward);

  Board bBlackAtTheEndLeftForward;
  bBlackAtTheEndLeftForward.put(Draught(cBlackJump3LeftForward, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack3, Color::EBlack, true));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherBlack4, Color::EBlack));
  bBlackAtTheEndLeftForward.put(Draught(cWhiteStart, Color::EWhite));
  bBlackAtTheEndLeftForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  m = analyser.createMove(csBlackAtTheEndLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackAtTheEndLeftForward, m.to());

  Board bBlackAtTheEndRightForward;
  bBlackAtTheEndRightForward.put(Draught(cBlackJump3RightForward, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack3, Color::EBlack, true));
  bBlackAtTheEndRightForward.put(Draught(cAnotherBlack4, Color::EBlack));
  bBlackAtTheEndRightForward.put(Draught(cWhiteStart, Color::EWhite));
  bBlackAtTheEndRightForward.put(Draught(cAnotherWhite1, Color::EWhite));
  m = analyser.createMove(csBlackAtTheEndRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackAtTheEndRightForward, m.to());

  CoordSequence csWhiteAtTheEndLeftForward(cWhiteStart, cWhiteJump1);
  csWhiteAtTheEndLeftForward.append(cWhiteJump2);
  CoordSequence csWhiteAtTheEndRightForward(csWhiteAtTheEndLeftForward);
  csWhiteAtTheEndLeftForward.append(cWhiteJump3LeftForward);
  csWhiteAtTheEndRightForward.append(cWhiteJump3RightForward);

  Board bWhiteAtTheEndLeftForward;
  bWhiteAtTheEndLeftForward.put(Draught(cBlackStart, Color::EBlack));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherBlack1, Color::EBlack));
  bWhiteAtTheEndLeftForward.put(Draught(cWhiteJump3LeftForward, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite3, Color::EWhite));
  bWhiteAtTheEndLeftForward.put(Draught(cAnotherWhite4, Color::EWhite));
  m = analyser.createMove(csWhiteAtTheEndLeftForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteAtTheEndLeftForward, m.to());

  Board bWhiteAtTheEndRightForward;
  bWhiteAtTheEndRightForward.put(Draught(cBlackStart, Color::EBlack));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherBlack2, Color::EBlack));
  bWhiteAtTheEndRightForward.put(Draught(cWhiteJump3RightForward, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite1, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite2, Color::EWhite, true));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite3, Color::EWhite));
  bWhiteAtTheEndRightForward.put(Draught(cAnotherWhite4, Color::EWhite));
  m = analyser.createMove(csWhiteAtTheEndRightForward);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteAtTheEndRightForward, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpByKing()
{
  const Coord cBlackStartE3('e', '3');
  const Coord cBlackG3('g', '3');
  const Coord cBlackE5('e', '5');
  const Coord cBlackG5('g', '5');
  const Coord cBlackE7('e', '7');
  const Coord cBlackG7('g', '7');
  const Coord cBlackJumpC1('c', '1');
  const Coord cBlackJumpA3('a', '3');
  const Coord cBlackJumpC5('c', '5');
  const Coord cBlackJumpA7('a', '7');

  const Coord cWhiteStartD6('d', '6');
  const Coord cWhiteB6('b', '6');
  const Coord cWhiteB4('b', '4');
  const Coord cWhiteD4('d', '4');
  const Coord cWhiteB2('b', '2');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteJumpF8('f', '8');
  const Coord cWhiteJumpH6('h', '6');
  const Coord cWhiteJumpF4('f', '4');
  const Coord cWhiteJumpH2('h', '2');

  Board b;
  b.put(Draught(cBlackStartE3, Color::EBlack, true));
  b.put(Draught(cBlackG3, Color::EBlack));
  b.put(Draught(cBlackG5, Color::EBlack));
  b.put(Draught(cBlackG7, Color::EBlack, true));
  b.put(Draught(cBlackE5, Color::EBlack));
  b.put(Draught(cBlackE7, Color::EBlack));
  b.put(Draught(cWhiteStartD6, Color::EWhite, true));
  b.put(Draught(cWhiteB6, Color::EWhite));
  b.put(Draught(cWhiteB4, Color::EWhite, true));
  b.put(Draught(cWhiteB2, Color::EWhite));
  b.put(Draught(cWhiteD4, Color::EWhite));
  b.put(Draught(cWhiteD2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackE3C1_E3(cBlackStartE3, cBlackJumpC1);
  csBlackE3C1_E3.append(cBlackJumpA3);
  csBlackE3C1_E3.append(cBlackJumpC5);
  CoordSequence csBlackE3C1_A7(csBlackE3C1_E3);
  csBlackE3C1_E3.append(cBlackStartE3);
  csBlackE3C1_A7.append(cBlackJumpA7);

  Board bBlackE3C1_E3;
  bBlackE3C1_E3.put(Draught(cBlackStartE3, Color::EBlack, true));
  bBlackE3C1_E3.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_E3.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_E3.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_E3.put(Draught(cWhiteB6, Color::EWhite));
  m = analyser.createMove(csBlackE3C1_E3);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_E3, m.to());
  CPPUNIT_ASSERT_EQUAL(csBlackE3C1_E3, analyser.createCoordSequence(m));

  Board bBlackE3C1_A7;
  bBlackE3C1_A7.put(Draught(cBlackJumpA7, Color::EBlack, true));
  bBlackE3C1_A7.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_A7.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_A7.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_A7.put(Draught(cWhiteD4, Color::EWhite));
  m = analyser.createMove(csBlackE3C1_A7);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_A7, m.to());
  CPPUNIT_ASSERT_EQUAL(csBlackE3C1_A7, analyser.createCoordSequence(m));

  CoordSequence csBlackE3C5_E3(cBlackStartE3, cBlackJumpC5);
  CoordSequence csBlackE3C5_A7(csBlackE3C5_E3);
  csBlackE3C5_E3.append(cBlackJumpA3);
  csBlackE3C5_E3.append(cBlackJumpC1);
  csBlackE3C5_E3.append(cBlackStartE3);
  csBlackE3C5_A7.append(cBlackJumpA7);

  m = analyser.createMove(csBlackE3C5_E3);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_E3, m.to()); //the same board as jump in another direction
  CPPUNIT_ASSERT_EQUAL(csBlackE3C5_E3, analyser.createCoordSequence(m));

  Board bBlackE3C5_A7;
  bBlackE3C5_A7.put(Draught(cBlackJumpA7, Color::EBlack, true));
  bBlackE3C5_A7.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C5_A7.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C5_A7.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C5_A7.put(Draught(cWhiteB4, Color::EWhite, true));
  bBlackE3C5_A7.put(Draught(cWhiteB2, Color::EWhite));
  bBlackE3C5_A7.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csBlackE3C5_A7);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C5_A7, m.to());
  CPPUNIT_ASSERT_EQUAL(csBlackE3C5_A7, analyser.createCoordSequence(m));

  CoordSequence csWhiteD6F8_D6(cWhiteStartD6, cWhiteJumpF8);
  csWhiteD6F8_D6.append(cWhiteJumpH6);
  csWhiteD6F8_D6.append(cWhiteJumpF4);
  CoordSequence csWhiteD6F8_H2(csWhiteD6F8_D6);
  csWhiteD6F8_D6.append(cWhiteStartD6);
  csWhiteD6F8_H2.append(cWhiteJumpH2);

  Board bWhiteD6F8_D6;
  bWhiteD6F8_D6.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_D6.put(Draught(cBlackG3, Color::EBlack));
  bWhiteD6F8_D6.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bWhiteD6F8_D6.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_D6.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_D6.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F8_D6);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_D6, m.to());
  CPPUNIT_ASSERT_EQUAL(csWhiteD6F8_D6, analyser.createCoordSequence(m));

  Board bWhiteD6F8_H2;
  bWhiteD6F8_H2.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_H2.put(Draught(cBlackE5, Color::EBlack));
  bWhiteD6F8_H2.put(Draught(cWhiteJumpH2, Color::EWhite, true));
  bWhiteD6F8_H2.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_H2.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_H2.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F8_H2);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_H2, m.to());
  CPPUNIT_ASSERT_EQUAL(csWhiteD6F8_H2, analyser.createCoordSequence(m));

  CoordSequence csWhiteD6F4_D6(cWhiteStartD6, cWhiteJumpF4);
  CoordSequence csWhiteD6F4_H2(csWhiteD6F4_D6);
  csWhiteD6F4_D6.append(cWhiteJumpH6);
  csWhiteD6F4_D6.append(cWhiteJumpF8);
  csWhiteD6F4_D6.append(cWhiteStartD6);
  csWhiteD6F4_H2.append(cWhiteJumpH2);

  m = analyser.createMove(csWhiteD6F4_D6);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_D6, m.to()); //the same board as jump in another direction
  CPPUNIT_ASSERT_EQUAL(csWhiteD6F4_D6, analyser.createCoordSequence(m));

  Board bWhiteD6F4_H2;
  bWhiteD6F4_H2.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F4_H2.put(Draught(cBlackG5, Color::EBlack));
  bWhiteD6F4_H2.put(Draught(cBlackG7, Color::EBlack, true));
  bWhiteD6F4_H2.put(Draught(cBlackE7, Color::EBlack));
  bWhiteD6F4_H2.put(Draught(cWhiteJumpH2, Color::EWhite, true));
  bWhiteD6F4_H2.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F4_H2.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F4_H2.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F4_H2.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F4_H2.put(Draught(cWhiteD2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F4_H2);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F4_H2, m.to());
  CPPUNIT_ASSERT_EQUAL(csWhiteD6F4_H2, analyser.createCoordSequence(m));
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpByKingOverKingRow()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpF6('f', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite, true));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D4(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D4.append(cBlackJumpD8);
  csBlackD4B6_D4.append(cBlackJumpF6);
  csBlackD4B6_D4.append(cBlackStartD4);
  Board bBlackD4_D4;
  bBlackD4_D4.put(Draught(cBlackStartD4, Color::EBlack, true));
  bBlackD4_D4.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4_D4.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4_D4.put(Draught(cBlackF2, Color::EBlack));
  m = analyser.createMove(csBlackD4B6_D4);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4_D4, m.to());

  CoordSequence csBlackD4F6_D4(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_D4.append(cBlackJumpD8);
  csBlackD4F6_D4.append(cBlackJumpB6);
  csBlackD4F6_D4.append(cBlackStartD4);
  m = analyser.createMove(csBlackD4F6_D4);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4_D4, m.to());

  CoordSequence csWhiteE5C3_E5(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E5.append(cWhiteJumpE1);
  csWhiteE5C3_E5.append(cWhiteJumpG3);
  csWhiteE5C3_E5.append(cWhiteStartE5);
  Board bWhiteE5_E5;
  bWhiteE5_E5.put(Draught(cWhiteStartE5, Color::EWhite, true));
  bWhiteE5_E5.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5_E5.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5_E5.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteE5C3_E5);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5_E5, m.to());

  CoordSequence csWhiteE5G3_E5(cWhiteStartE5, cWhiteJumpG3);
  csWhiteE5G3_E5.append(cWhiteJumpE1);
  csWhiteE5G3_E5.append(cWhiteJumpC3);
  csWhiteE5G3_E5.append(cWhiteStartE5);
  m = analyser.createMove(csWhiteE5G3_E5);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5_E5, m.to());
}
void AmericanCheckersPositionAnalyserTests::createComplexJumpByKingOverStartSquare()
{
  const Coord cBlackStartE3('e', '3');
  const Coord cBlackG3('g', '3');
  const Coord cBlackE5('e', '5');
  const Coord cBlackG5('g', '5');
  const Coord cBlackE7('e', '7');
  const Coord cBlackG7('g', '7');
  const Coord cBlackC7('c', '7');
  const Coord cBlackJumpC1('c', '1');
  const Coord cBlackJumpA3('a', '3');
  const Coord cBlackJumpC5('c', '5');
  const Coord cBlackJumpG1('g', '1');

  const Coord cWhiteStartD6('d', '6');
  const Coord cWhiteB6('b', '6');
  const Coord cWhiteB4('b', '4');
  const Coord cWhiteD4('d', '4');
  const Coord cWhiteB2('b', '2');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteF2('f', '2');
  const Coord cWhiteJumpF8('f', '8');
  const Coord cWhiteJumpH6('h', '6');
  const Coord cWhiteJumpF4('f', '4');
  const Coord cWhiteJumpB8('b', '8');

  Board b;
  b.put(Draught(cBlackStartE3, Color::EBlack, true));
  b.put(Draught(cBlackG3, Color::EBlack));
  b.put(Draught(cBlackG5, Color::EBlack));
  b.put(Draught(cBlackG7, Color::EBlack, true));
  b.put(Draught(cBlackE5, Color::EBlack));
  b.put(Draught(cBlackE7, Color::EBlack));
  b.put(Draught(cBlackC7, Color::EBlack, true));
  b.put(Draught(cWhiteStartD6, Color::EWhite, true));
  b.put(Draught(cWhiteB6, Color::EWhite));
  b.put(Draught(cWhiteB4, Color::EWhite, true));
  b.put(Draught(cWhiteB2, Color::EWhite));
  b.put(Draught(cWhiteD4, Color::EWhite));
  b.put(Draught(cWhiteD2, Color::EWhite));
  b.put(Draught(cWhiteF2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackE3C1_G1(cBlackStartE3, cBlackJumpC1);
  csBlackE3C1_G1.append(cBlackJumpA3);
  csBlackE3C1_G1.append(cBlackJumpC5);
  csBlackE3C1_G1.append(cBlackStartE3);
  csBlackE3C1_G1.append(cBlackJumpG1);

  Board bBlackE3C1_G1;
  bBlackE3C1_G1.put(Draught(cBlackJumpG1, Color::EBlack, true));
  bBlackE3C1_G1.put(Draught(cBlackG3, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackG5, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackE3C1_G1.put(Draught(cBlackE5, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackE7, Color::EBlack));
  bBlackE3C1_G1.put(Draught(cBlackC7, Color::EBlack, true));
  bBlackE3C1_G1.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackE3C1_G1.put(Draught(cWhiteB6, Color::EWhite));
  m = analyser.createMove(csBlackE3C1_G1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackE3C1_G1, m.to());

  CoordSequence csWhiteD6F8_B8(cWhiteStartD6, cWhiteJumpF8);
  csWhiteD6F8_B8.append(cWhiteJumpH6);
  csWhiteD6F8_B8.append(cWhiteJumpF4);
  csWhiteD6F8_B8.append(cWhiteStartD6);
  csWhiteD6F8_B8.append(cWhiteJumpB8);

  Board bWhiteD6F8_B8;
  bWhiteD6F8_B8.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteD6F8_B8.put(Draught(cBlackG3, Color::EBlack));
  bWhiteD6F8_B8.put(Draught(cWhiteJumpB8, Color::EWhite, true));
  bWhiteD6F8_B8.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteD6F8_B8.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteD2, Color::EWhite));
  bWhiteD6F8_B8.put(Draught(cWhiteF2, Color::EWhite));
  m = analyser.createMove(csWhiteD6F8_B8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteD6F8_B8, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpGetKing()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpB8('b', '8');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF6('f', '6');
  const Coord cBlackJumpF8('f', '8');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpC1('c', '1');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpG3('g', '3');
  const Coord cWhiteJumpG1('g', '1');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D8(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D8.append(cBlackJumpD8);
  Board bBlackD4B6_D8;
  bBlackD4B6_D8.put(Draught(cBlackJumpD8, Color::EBlack, true));
  bBlackD4B6_D8.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cBlackF2, Color::EBlack));
  bBlackD4B6_D8.put(Draught(cWhiteStartE5, Color::EWhite));
  bBlackD4B6_D8.put(Draught(cWhiteE7, Color::EWhite));
  m = analyser.createMove(csBlackD4B6_D8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4B6_D8, m.to());

  CoordSequence csBlackD4F6_D8(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_D8.append(cBlackJumpD8);
  Board bBlackD4F6_D8;
  bBlackD4F6_D8.put(Draught(cBlackJumpD8, Color::EBlack, true));
  bBlackD4F6_D8.put(Draught(cBlackD2, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cBlackF4, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cBlackF2, Color::EBlack));
  bBlackD4F6_D8.put(Draught(cWhiteC5, Color::EWhite));
  bBlackD4F6_D8.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csBlackD4F6_D8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackD4F6_D8, m.to());

  CoordSequence csBlackF4D6_B8(cBlackF4, cBlackJumpD6);
  csBlackF4D6_B8.append(cBlackJumpB8);
  Board bBlackF4D6_B8;
  bBlackF4D6_B8.put(Draught(cBlackJumpB8, Color::EBlack, true));
  bBlackF4D6_B8.put(Draught(cBlackD2, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cBlackStartD4, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cBlackF2, Color::EBlack));
  bBlackF4D6_B8.put(Draught(cWhiteE7, Color::EWhite));
  bBlackF4D6_B8.put(Draught(cWhiteC5, Color::EWhite));
  m = analyser.createMove(csBlackF4D6_B8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackF4D6_B8, m.to());

  CoordSequence csBlackF4D6_F8(cBlackF4, cBlackJumpD6);
  csBlackF4D6_F8.append(cBlackJumpF8);
  Board bBlackF4D6_F8;
  bBlackF4D6_F8.put(Draught(cBlackJumpF8, Color::EBlack, true));
  bBlackF4D6_F8.put(Draught(cBlackD2, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cBlackStartD4, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cBlackF2, Color::EBlack));
  bBlackF4D6_F8.put(Draught(cWhiteC5, Color::EWhite));
  bBlackF4D6_F8.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csBlackF4D6_F8);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bBlackF4D6_F8, m.to());

  CoordSequence csWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E1.append(cWhiteJumpE1);
  Board bWhiteE5C3_E1;
  bWhiteE5C3_E1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteE5C3_E1.put(Draught(cBlackF2, Color::EBlack));
  bWhiteE5C3_E1.put(Draught(cWhiteJumpE1, Color::EWhite, true));
  bWhiteE5C3_E1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5C3_E1.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5C3_E1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteE5C3_E1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5C3_E1, m.to());

  CoordSequence csWhiteE5G3_E1(cWhiteStartE5, cWhiteJumpG3);
  csWhiteE5G3_E1.append(cWhiteJumpE1);
  Board bWhiteE5G3_E1;
  bWhiteE5G3_E1.put(Draught(cBlackStartD4, Color::EBlack));
  bWhiteE5G3_E1.put(Draught(cBlackD2, Color::EBlack));
  bWhiteE5G3_E1.put(Draught(cWhiteJumpE1, Color::EWhite, true));
  bWhiteE5G3_E1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteE5G3_E1.put(Draught(cWhiteC5, Color::EWhite));
  bWhiteE5G3_E1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteE5G3_E1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteE5G3_E1, m.to());

  CoordSequence csWhiteC5E3_C1(cWhiteC5, cWhiteJumpE3);
  csWhiteC5E3_C1.append(cWhiteJumpC1);
  Board bWhiteC5E3_C1;
  bWhiteC5E3_C1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteC5E3_C1.put(Draught(cBlackF2, Color::EBlack));
  bWhiteC5E3_C1.put(Draught(cWhiteJumpC1, Color::EWhite, true));
  bWhiteC5E3_C1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteC5E3_C1.put(Draught(cWhiteStartE5, Color::EWhite));
  bWhiteC5E3_C1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteC5E3_C1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteC5E3_C1, m.to());

  CoordSequence csWhiteC5E3_G1(cWhiteC5, cWhiteJumpE3);
  csWhiteC5E3_G1.append(cWhiteJumpG1);
  Board bWhiteC5E3_G1;
  bWhiteC5E3_G1.put(Draught(cBlackD2, Color::EBlack));
  bWhiteC5E3_G1.put(Draught(cBlackF4, Color::EBlack));
  bWhiteC5E3_G1.put(Draught(cWhiteJumpG1, Color::EWhite, true));
  bWhiteC5E3_G1.put(Draught(cWhiteE7, Color::EWhite));
  bWhiteC5E3_G1.put(Draught(cWhiteStartE5, Color::EWhite));
  bWhiteC5E3_G1.put(Draught(cWhiteC7, Color::EWhite));
  m = analyser.createMove(csWhiteC5E3_G1);
  CPPUNIT_ASSERT_EQUAL(b, m.from());
  CPPUNIT_ASSERT_EQUAL(bWhiteC5E3_G1, m.to());
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpNoRequestedDraught()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackJumpB8('b', '8');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF4('f', '4');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackF4D6_B8(cBlackJumpF4, cBlackJumpD6);
  csBlackF4D6_B8.append(cBlackJumpB8);
  m = analyser.createMove(csBlackF4D6_B8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorNoRequestedDraught);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpNothingToJumpOver()
{
  const Coord cBlackStartF4('f', '4');
  const Coord cBlackJumpB8('b', '8');
  const Coord cBlackJumpD6('d', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');

  Board b;
  b.put(Draught(cBlackStartF4, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackF4D6_B8(cBlackStartF4, cBlackJumpD6);
  csBlackF4D6_B8.append(cBlackJumpB8);
  m = analyser.createMove(csBlackF4D6_B8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorNothingToJumpOver);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpInWrongDirection()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackJumpB4('b', '4');
  const Coord cBlackJumpD6('d', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpG5('g', '5');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackF4D6_B4(cBlackF4, cBlackJumpD6);
  csBlackF4D6_B4.append(cBlackJumpB4);
  m = analyser.createMove(csBlackF4D6_B4);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);

  CoordSequence csWhiteC5E3_G5(cWhiteC5, cWhiteJumpE3);
  csWhiteC5E3_G5.append(cWhiteJumpG5);
  m = analyser.createMove(csWhiteC5E3_G5);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorInWrongDirection);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpToBusySquare()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackF8('f', '8');
  const Coord cBlackC1('c', '1');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD6('d', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteD8('d', '8');
  const Coord cWhiteE1('e', '1');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE3('e', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cBlackC1, Color::EBlack));
  b.put(Draught(cBlackF8, Color::EBlack, true));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));
  b.put(Draught(cWhiteD8, Color::EWhite));
  b.put(Draught(cWhiteE1, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D8(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D8.append(cWhiteD8);
  m = analyser.createMove(csBlackD4B6_D8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csBlackF4D6_F8(cBlackF4, cBlackJumpD6);
  csBlackF4D6_F8.append(cBlackF8);
  m = analyser.createMove(csBlackF4D6_F8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E1.append(cWhiteE1);
  m = analyser.createMove(csWhiteE5C3_E1);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteC5E3_C1(cWhiteC5, cWhiteJumpE3);
  csWhiteC5E3_C1.append(cBlackC1);
  m = analyser.createMove(csWhiteC5E3_C1);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpOverBusySquare()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackF8('f', '8');
  const Coord cBlackC1('c', '1');
  const Coord cBlackB4('b', '4');
  const Coord cBlackB2('b', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF6('f', '6');
  const Coord cBlackJumpH6('h', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteD8('d', '8');
  const Coord cWhiteE1('e', '1');
  const Coord cWhiteA5('a', '5');
  const Coord cWhiteG7('g', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpA3('a', '3');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack, true));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cBlackC1, Color::EBlack));
  b.put(Draught(cBlackB2, Color::EBlack));
  b.put(Draught(cBlackB4, Color::EBlack));
  b.put(Draught(cBlackF8, Color::EBlack, true));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite, true));
  b.put(Draught(cWhiteC7, Color::EWhite));
  b.put(Draught(cWhiteD8, Color::EWhite));
  b.put(Draught(cWhiteE1, Color::EWhite, true));
  b.put(Draught(cWhiteA5, Color::EWhite, true));
  b.put(Draught(cWhiteG7, Color::EWhite, true));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4F6_B6(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_B6.append(cWhiteD8);
  csBlackD4F6_B6.append(cBlackJumpB6);
  m = analyser.createMove(csBlackD4F6_B6);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csBlackF4D6_H6(cBlackF4, cBlackJumpD6);
  csBlackF4D6_H6.append(cBlackF8);
  csBlackF4D6_H6.append(cBlackJumpH6);
  m = analyser.createMove(csBlackF4D6_H6);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteA5C3_G3(cWhiteA5, cWhiteJumpC3);
  csWhiteA5C3_G3.append(cWhiteE1);
  csWhiteA5C3_G3.append(cWhiteJumpG3);
  m = analyser.createMove(csWhiteA5C3_G3);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);

  CoordSequence csWhiteC5A3_E3(cWhiteC5, cWhiteJumpA3);
  csWhiteC5A3_E3.append(cBlackC1);
  csWhiteC5A3_E3.append(cWhiteJumpE3);
  m = analyser.createMove(csWhiteC5A3_E3);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorBusySquare);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpMoreJumpExist()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpF6('f', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack, true));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite, true));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D8(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D8.append(cBlackJumpD8);
  m = analyser.createMove(csBlackD4B6_D8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csBlackD4F6_D8(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_D8.append(cBlackJumpD8);
  m = analyser.createMove(csBlackD4F6_D8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csBlackF4D6(cBlackF4, cBlackJumpD6);
  m = analyser.createMove(csBlackF4D6);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csWhiteE5C3_E1(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E1.append(cWhiteJumpE1);
  m = analyser.createMove(csWhiteE5C3_E1);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csWhiteE5G3_E1(cWhiteStartE5, cWhiteJumpG3);
  csWhiteE5G3_E1.append(cWhiteJumpE1);
  m = analyser.createMove(csWhiteE5G3_E1);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);

  CoordSequence csWhiteC5E3(cWhiteC5, cWhiteJumpE3);
  m = analyser.createMove(csWhiteC5E3);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpExist);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpNotTerminatedAfterGetKing()
{
  const Coord cBlackStartD4('d', '4');
  const Coord cBlackF4('f', '4');
  const Coord cBlackD2('d', '2');
  const Coord cBlackF2('f', '2');
  const Coord cBlackJumpB6('b', '6');
  const Coord cBlackJumpD8('d', '8');
  const Coord cBlackJumpF6('f', '6');

  const Coord cWhiteStartE5('e', '5');
  const Coord cWhiteC5('c', '5');
  const Coord cWhiteC7('c', '7');
  const Coord cWhiteE7('e', '7');
  const Coord cWhiteJumpC3('c', '3');
  const Coord cWhiteJumpE1('e', '1');
  const Coord cWhiteJumpG3('g', '3');

  Board b;
  b.put(Draught(cBlackStartD4, Color::EBlack));
  b.put(Draught(cBlackD2, Color::EBlack));
  b.put(Draught(cBlackF4, Color::EBlack));
  b.put(Draught(cBlackF2, Color::EBlack));
  b.put(Draught(cWhiteStartE5, Color::EWhite));
  b.put(Draught(cWhiteE7, Color::EWhite));
  b.put(Draught(cWhiteC5, Color::EWhite));
  b.put(Draught(cWhiteC7, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackD4B6_D4(cBlackStartD4, cBlackJumpB6);
  csBlackD4B6_D4.append(cBlackJumpD8);
  csBlackD4B6_D4.append(cBlackJumpF6);
  csBlackD4B6_D4.append(cBlackStartD4);
  m = analyser.createMove(csBlackD4B6_D4);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorGetKingButMoveFurther);

  CoordSequence csBlackD4F6_D4(cBlackStartD4, cBlackJumpF6);
  csBlackD4F6_D4.append(cBlackJumpD8);
  csBlackD4F6_D4.append(cBlackJumpB6);
  csBlackD4F6_D4.append(cBlackStartD4);
  m = analyser.createMove(csBlackD4F6_D4);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorGetKingButMoveFurther);

  CoordSequence csWhiteE5C3_E5(cWhiteStartE5, cWhiteJumpC3);
  csWhiteE5C3_E5.append(cWhiteJumpE1);
  csWhiteE5C3_E5.append(cWhiteJumpG3);
  csWhiteE5C3_E5.append(cWhiteStartE5);
  m = analyser.createMove(csWhiteE5C3_E5);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorGetKingButMoveFurther);

  CoordSequence csWhiteE5G3_E5(cWhiteStartE5, cWhiteJumpG3);
  csWhiteE5G3_E5.append(cWhiteJumpE1);
  csWhiteE5G3_E5.append(cWhiteJumpC3);
  csWhiteE5G3_E5.append(cWhiteStartE5);
  m = analyser.createMove(csWhiteE5G3_E5);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorGetKingButMoveFurther);
}

void AmericanCheckersPositionAnalyserTests::createComplexJumpOverSameColor()
{
  const Coord cBlackStartF4('f', '4');
  const Coord cBlackD4('d', '4');
  const Coord cBlackC7('c', '7');
  const Coord cBlackJumpD6('d', '6');
  const Coord cBlackJumpB8('b', '8');

  const Coord cWhiteStartC5('c', '5');
  const Coord cWhiteE5('e', '5');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteJumpE3('e', '3');
  const Coord cWhiteJumpC1('c', '1');

  Board b;
  b.put(Draught(cBlackStartF4, Color::EBlack));
  b.put(Draught(cBlackD4, Color::EBlack));
  b.put(Draught(cBlackC7, Color::EBlack));
  b.put(Draught(cWhiteStartC5, Color::EWhite));
  b.put(Draught(cWhiteE5, Color::EWhite));
  b.put(Draught(cWhiteD2, Color::EWhite));

  AmericanCheckersPositionAnalyser analyser;
  analyser.setPosition(b);
  Move m;

  CoordSequence csBlackF4D6_B8(cBlackStartF4, cBlackJumpD6);
  csBlackF4D6_B8.append(cBlackJumpB8);
  m = analyser.createMove(csBlackF4D6_B8);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpOverSameColor);

  CoordSequence csWhiteC5E3_C1(cWhiteStartC5, cWhiteJumpE3);
  csWhiteC5E3_C1.append(cWhiteJumpC1);
  m = analyser.createMove(csWhiteC5E3_C1);
  CPPUNIT_ASSERT_THROW(m.to(), Move::ErrorJumpOverSameColor);
}

void AmericanCheckersPositionAnalyserTests::createCoordSequenceFromMoveRandom()
{
  const Coord cBlackStartE3('e', '3');
  const Coord cBlackG3('g', '3');
  const Coord cBlackE5('e', '5');
  const Coord cBlackG5('g', '5');
  const Coord cBlackE7('e', '7');
  const Coord cBlackG7('g', '7');
  const Coord cBlackJumpC1('c', '1');
  const Coord cBlackJumpA3('a', '3');
  const Coord cBlackJumpC5('c', '5');
  const Coord cBlackJumpA7('a', '7');

  const Coord cWhiteStartD6('d', '6');
  const Coord cWhiteB6('b', '6');
  const Coord cWhiteB4('b', '4');
  const Coord cWhiteD4('d', '4');
  const Coord cWhiteB2('b', '2');
  const Coord cWhiteD2('d', '2');
  const Coord cWhiteJumpF8('f', '8');
  const Coord cWhiteJumpH6('h', '6');
  const Coord cWhiteJumpF4('f', '4');
  const Coord cWhiteJumpH2('h', '2');

  AmericanCheckersPositionAnalyser analyser;
  typedef std::set<CoordSequence> CoordSequenceSet;
  CoordSequenceSet csTestSet;
  const int attemptCount = 10;

  Board bFrom;
  bFrom.put(Draught(cBlackStartE3, Color::EBlack, true));
  bFrom.put(Draught(cBlackG3, Color::EBlack));
  bFrom.put(Draught(cBlackG5, Color::EBlack));
  bFrom.put(Draught(cBlackG7, Color::EBlack, true));
  bFrom.put(Draught(cBlackE5, Color::EBlack));
  bFrom.put(Draught(cBlackE7, Color::EBlack));
  bFrom.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bFrom.put(Draught(cWhiteB6, Color::EWhite));
  bFrom.put(Draught(cWhiteB4, Color::EWhite, true));
  bFrom.put(Draught(cWhiteB2, Color::EWhite));
  bFrom.put(Draught(cWhiteD4, Color::EWhite));
  bFrom.put(Draught(cWhiteD2, Color::EWhite));

  Board bBlackTo;
  bBlackTo.put(Draught(cBlackStartE3, Color::EBlack, true));
  bBlackTo.put(Draught(cBlackG3, Color::EBlack));
  bBlackTo.put(Draught(cBlackG5, Color::EBlack));
  bBlackTo.put(Draught(cBlackG7, Color::EBlack, true));
  bBlackTo.put(Draught(cBlackE5, Color::EBlack));
  bBlackTo.put(Draught(cBlackE7, Color::EBlack));
  bBlackTo.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bBlackTo.put(Draught(cWhiteB6, Color::EWhite));

  CoordSequence csBlackE3C1_E3(cBlackStartE3, cBlackJumpC1);
  csBlackE3C1_E3.append(cBlackJumpA3);
  csBlackE3C1_E3.append(cBlackJumpC5);
  csBlackE3C1_E3.append(cBlackStartE3);

  CoordSequence csBlackE3C5_E3(cBlackStartE3, cBlackJumpC5);
  csBlackE3C5_E3.append(cBlackJumpA3);
  csBlackE3C5_E3.append(cBlackJumpC1);
  csBlackE3C5_E3.append(cBlackStartE3);

  Move mBlack(bFrom, bBlackTo);

  for(int i = 0; i < attemptCount; ++i)
    csTestSet.insert(analyser.createCoordSequence(mBlack));

  CPPUNIT_ASSERT_EQUAL(2, (int)csTestSet.size());

  for(CoordSequenceSet::const_iterator it = csTestSet.begin(); it != csTestSet.end(); ++it)
    CPPUNIT_ASSERT((*it) == csBlackE3C5_E3 || (*it) == csBlackE3C1_E3);

  csTestSet.clear();

  Board bWhiteTo;
  bWhiteTo.put(Draught(cBlackStartE3, Color::EBlack, true));
  bWhiteTo.put(Draught(cBlackG3, Color::EBlack));
  bWhiteTo.put(Draught(cWhiteStartD6, Color::EWhite, true));
  bWhiteTo.put(Draught(cWhiteB6, Color::EWhite));
  bWhiteTo.put(Draught(cWhiteB4, Color::EWhite, true));
  bWhiteTo.put(Draught(cWhiteB2, Color::EWhite));
  bWhiteTo.put(Draught(cWhiteD4, Color::EWhite));
  bWhiteTo.put(Draught(cWhiteD2, Color::EWhite));

  CoordSequence csWhiteD6F8_D6(cWhiteStartD6, cWhiteJumpF8);
  csWhiteD6F8_D6.append(cWhiteJumpH6);
  csWhiteD6F8_D6.append(cWhiteJumpF4);
  csWhiteD6F8_D6.append(cWhiteStartD6);

  CoordSequence csWhiteD6F4_D6(cWhiteStartD6, cWhiteJumpF4);
  csWhiteD6F4_D6.append(cWhiteJumpH6);
  csWhiteD6F4_D6.append(cWhiteJumpF8);
  csWhiteD6F4_D6.append(cWhiteStartD6);

  Move mWhite(bFrom, bWhiteTo);

  for(int i = 0; i < attemptCount; ++i)
    csTestSet.insert(analyser.createCoordSequence(mWhite));

  CPPUNIT_ASSERT_EQUAL(2, (int)csTestSet.size());

  for(CoordSequenceSet::const_iterator it = csTestSet.begin(); it != csTestSet.end(); ++it)
    CPPUNIT_ASSERT((*it) == csWhiteD6F8_D6 || (*it) == csWhiteD6F4_D6);
}

void AmericanCheckersPositionAnalyserTests::createCoordSequenceFromMoveNotFound()
{
  const Coord cBlackD4('d', '4');
  const Coord cWhiteE5('e', '5');
  const Coord cBlackToC5('c', '5');

  Board from;
  from.put(Draught(cBlackD4, Color::EBlack));
  from.put(Draught(cWhiteE5, Color::EWhite));

  Board to;
  to.put(Draught(cBlackToC5, Color::EBlack));
  to.put(Draught(cWhiteE5, Color::EWhite));

  Move m(from, to);
  AmericanCheckersPositionAnalyser analyser;
  CPPUNIT_ASSERT_THROW(analyser.createCoordSequence(m), AmericanCheckersPositionAnalyser::ErrorNotFound);
}
