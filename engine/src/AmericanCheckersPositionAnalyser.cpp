#include "AmericanCheckersPositionAnalyser.h"
#include "Move.h"
#include "RulesOfGame.h"
#include "CoordDelta.h"

#include <iostream>

using namespace Checkers::Engine;


AmericanCheckersPositionAnalyser::AmericanCheckersPositionAnalyser()
  : m_color(Color::EBlack)
  , m_jump_found(false)
{
}

void AmericanCheckersPositionAnalyser::setPosition(const Engine::Board &aBoard, const Engine::Color &aColor)
{
  m_from = aBoard;
  updateValidMovesIfNeeded(aColor, true);
}

Move AmericanCheckersPositionAnalyser::createMove(const Engine::CoordSequence &aCoorsSequence, bool aUpdateColorIfNeeded)
{
  Board to(m_from);
  Move move;

  Maybe<Draught> moved = m_from.testSquare(*aCoorsSequence.begin());

  if(moved.isNothing())
  {
    //TODO: add error handling after refactoring to the new design
    //throw Engine::Error::Ptr(new Move::ErrorUnknown);
    //TODO rework below
    return Move(Engine::Error::Ptr(new Move::ErrorNoRequestedDraught));
  }

  if(aUpdateColorIfNeeded)
  {
    updateValidMovesIfNeeded(moved().color());
  }
  else
  {
    if(m_color != moved().color())
    {
      //TODO: add error handling after refactoring to the new design
      throw Engine::Error::Ptr(new Move::ErrorUnknown);
    }
  }

  CoordSequenceToBoardMap::const_iterator found = m_seq_board_map.find(aCoorsSequence);

  if(found != m_seq_board_map.end())
  {
    move = Move(m_from, *(found->second));
  }
  else
  {
    try
    {
      ActionAtBoard::Ptr action = RulesOfGame::MoveValidator::transformIntoActions(m_from, aCoorsSequence);

      if(!action)
        throw Engine::Error::Ptr(new Move::ErrorUnknown);

      action->perform(to);

      move = Move(m_from, to);
    }
    catch(Engine::Error::Ptr e)
    {
      move = Move(e);
    }
  }

  return move;
}

const PositionAnalyser::MoveList & AmericanCheckersPositionAnalyser::validMoves()
{
  if(m_valid_moves.size() == 0)
  {
    for(BoardStorage::const_iterator it = m_tos.begin(); it != m_tos.end(); ++it)
      m_valid_moves.push_back(Move(m_from, *it));
  }

  return m_valid_moves;
}

void AmericanCheckersPositionAnalyser::reset()
{
    m_jump_found = false;
    m_valid_moves.clear();
    m_seq_board_map.clear();
    m_tos.clear();
    searchReset();
}

void AmericanCheckersPositionAnalyser::updateValidMovesIfNeeded(const Engine::Color &aColor, bool aForced)
{
  if(aForced || aColor != m_color)
  {
    m_color = aColor;

    reset();
    searchForValidMoves();
  }
}

void AmericanCheckersPositionAnalyser::searchForValidMoves()
{
  for(Board::Iterator it = m_from.begin(); it != m_from.end(); ++it)
  {
    if(it->color() == m_color)
    {
      CoordSequence csAccumulator;
      csAccumulator.append(it->coord());
      searchForJumps(csAccumulator, m_from, *it, false);

      if(m_jump_found)
        continue;

      searchForSimpleMoves(m_from, *it);
    }
  }
}

void AmericanCheckersPositionAnalyser::searchForJumps(CoordSequence &aAccum, const Engine::Board &aBoard, const Engine::Draught &aDraught, bool aGotKing)
{
  CoordDelta::Direction directions[4] = {
                          CoordDelta::ENorthWest
                        , CoordDelta::ENorthEast
                        , CoordDelta::ESouthEast
                        , CoordDelta::ESouthWest
                        };

  int firstDirectionIndex = aDraught.isKing()? 0 : aDraught.color() == Color::EBlack ? 0 : 2;
  int lastDirectionIndex = aDraught.isKing()? 3 : aDraught.color() == Color::EBlack ? 1 : 3;

  bool jumpNotFound = true;

  for(int directionIndex = firstDirectionIndex; directionIndex <= lastDirectionIndex; ++directionIndex)
  {
    try
    {
      Coord jumpToCoord = aDraught.coord() + CoordDelta(directions[directionIndex], 2);
      Coord jumpedCoord = aDraught.coord() + CoordDelta(directions[directionIndex], 1);

      Maybe<Draught> jumpedDraught = aBoard.testSquare(jumpedCoord);
      Maybe<Draught> jumpToDraught = aBoard.testSquare(jumpToCoord);

      if(!aGotKing && !jumpedDraught.isNothing() && jumpedDraught().color() != aDraught.color() && jumpToDraught.isNothing())
      {
        jumpNotFound = false;

        if(!m_jump_found)
        {
          reset();
          m_jump_found = true;
        }

        aAccum.append(jumpToCoord);

        Board testBoard(aBoard);
        Draught moved = testBoard.takeDraught(aDraught.coord())();
        bool gotKing = !moved.isKing() && RulesOfGame::BoardBounds::isKingLine(jumpToCoord.y(), moved.color());
        if(gotKing)
        {
          moved.makeKing();
        }
        moved.moveTo(jumpToCoord);
        testBoard.put(moved);
        testBoard.takeDraught(jumpedCoord);

        searchForJumps(aAccum, testBoard, moved, gotKing);

        aAccum.pop();
      }
    }
    catch(Coord::ErrorIntWrongCoord e)
    {
      continue;
    }
  }

  if(jumpNotFound && aAccum.count() > 1)
  {
    BSInsertResult ret = m_tos.insert(aBoard);
    m_seq_board_map.insert(CoordSequenceToBoardMap::value_type(aAccum, ret.first));
  }
}

void AmericanCheckersPositionAnalyser::searchForSimpleMoves(const Engine::Board &aBoard, const Engine::Draught &aDraught)
{
  CoordDelta::Direction directions[4] = {
                          CoordDelta::ENorthWest
                        , CoordDelta::ENorthEast
                        , CoordDelta::ESouthEast
                        , CoordDelta::ESouthWest
                        };

  int firstDirectionIndex = aDraught.isKing()? 0 : aDraught.color() == Color::EBlack ? 0 : 2;
  int lastDirectionIndex = aDraught.isKing()? 3 : aDraught.color() == Color::EBlack ? 1 : 3;

  for(int directionIndex = firstDirectionIndex; directionIndex <= lastDirectionIndex; ++directionIndex)
  {
    try
    {
      Coord moveToCoord = aDraught.coord() + CoordDelta(directions[directionIndex], 1);

      Maybe<Draught> moveToDraught = aBoard.testSquare(moveToCoord);

      if(moveToDraught.isNothing())
      {
        Board testBoard(aBoard);
        Draught moved = testBoard.takeDraught(aDraught.coord())();
        moved.moveTo(moveToCoord);
        if(RulesOfGame::BoardBounds::isKingLine(moveToCoord.y(), moved.color()))
        {
          moved.makeKing();
        }
        testBoard.put(moved);

        BSInsertResult ret = m_tos.insert(testBoard);
        m_seq_board_map.insert(CoordSequenceToBoardMap::value_type(CoordSequence(aDraught.coord(), moveToCoord), ret.first));
      }
    }
    catch(Coord::ErrorIntWrongCoord e)
    {
      continue;
    }
  }
}

void AmericanCheckersPositionAnalyser::initSearchFilter()
{
  if(stepCount() < 0)
  {
    SearchMap zeroMap;

    for(CoordSequenceToBoardMap::const_iterator it = m_seq_board_map.begin(); it != m_seq_board_map.end(); ++it)
    {
      zeroMap.insert(SearchMap::value_type(it->first.begin(), it));
    }

    m_search_filter.push_back(zeroMap);
  }
  else
  {
    backToZeroStep();
  }
}

void AmericanCheckersPositionAnalyser::searchReset()
{
    m_search_filter.clear();
}


void AmericanCheckersPositionAnalyser::backToZeroStep()
{
  while(stepCount() > 0)
    undoSearchStep();
}

bool AmericanCheckersPositionAnalyser::doSearchStep(const Engine::CoordSequence::Iterator &aCoordI)
{
  typedef std::pair<SearchMap::const_iterator, SearchMap::const_iterator> FoundRange;
  FoundRange foundRange = lastStep()->equal_range(aCoordI);

  SearchMap nextMap;

  for(SearchMap::const_iterator it = foundRange.first; it != foundRange.second; ++it)
  {
    const CoordSequence & seq = it->second->first;
    CoordSequence::Iterator tempIter = it->first;

    if(tempIter != seq.last())
    {
      ++tempIter;
    }

    nextMap.insert(SearchMap::value_type(tempIter, it->second));
  }

  m_search_filter.push_back(nextMap);

  return isFound();
}

void AmericanCheckersPositionAnalyser::undoSearchStep()
{
  if(stepCount() < 0)
    throw Engine::Error();

  m_search_filter.pop_back();
}

bool AmericanCheckersPositionAnalyser::isFound() const
{
  return lastStep()->size() == 1;
}

bool AmericanCheckersPositionAnalyser::noVariant() const
{
  return lastStep()->size() == 0;
}

const Board & AmericanCheckersPositionAnalyser::fountTo() const
{
  if(!isFound())
    throw Engine::Error();

  return *(lastStep()->begin()->second->second);
}

const CoordSequence & AmericanCheckersPositionAnalyser::foundSequence() const
{
  if(!isFound())
    throw Engine::Error();

  return lastStep()->begin()->second->first;
}

AmericanCheckersPositionAnalyser::SearchFilter::const_iterator AmericanCheckersPositionAnalyser::lastStep() const
{
  if(stepCount() < 0)
    throw Engine::Error();

  return --m_search_filter.end();
}

int AmericanCheckersPositionAnalyser::stepCount() const
{
  return m_search_filter.size() - 1;
}
