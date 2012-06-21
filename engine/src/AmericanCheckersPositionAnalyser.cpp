#include "AmericanCheckersPositionAnalyser.h"
#include "Move.h"
#include "RulesOfGame.h"
#include "CoordDelta.h"

#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace Checkers::Engine;


AmericanCheckersPositionAnalyser::AmericanCheckersPositionAnalyser()
  : m_color(Color::EBlack)
{
}

void AmericanCheckersPositionAnalyser::setPosition(const Engine::Board &aBoard, const Engine::Color &aColor)
{
  m_from = aBoard;
  updateValidMovesIfNeeded(aColor, true);
  srand(time(0));
}

Move AmericanCheckersPositionAnalyser::createMove(const Engine::CoordSequence &aCoordSequence, bool aUpdateColorIfNeeded)
{
  Move move;

  if(aUpdateColorIfNeeded)
    safeColorUpdate(*aCoordSequence.begin());

  move = findInValidMoves(aCoordSequence);

  return move;
}

Move AmericanCheckersPositionAnalyser::findInValidMoves(const Engine::CoordSequence &aCoordSequence)
{
  Move move;

  initSearchFilter();

  CoordSequence::Iterator it = aCoordSequence.begin();
  for(; it != aCoordSequence.end() && !noVariant(); ++it)
  {
    bool isLastCoord = (it == aCoordSequence.last());

    if(doSearchStep(it) && isLastCoord && stepCount() == foundSequence().count())
    {
      move = foundMove();
      move.setCoordSequenceId(foundCoordSequenceId());
    }
  }

  if(!move.isValid())
  {
    move = createErrorMove(aCoordSequence, --it);
  }

  return move;
}

Move AmericanCheckersPositionAnalyser::createErrorMove(const Engine::CoordSequence &aCoordSequence, const Engine::CoordSequence::Iterator &aErrorLocation) const
{
  Move move;

  //TODO optimization required probably
  Maybe<Draught> moved = m_from.testSquare(*aCoordSequence.begin());
  bool isFirsCoord = (aErrorLocation == aCoordSequence.begin());
  CoordSequence::Iterator to = isFirsCoord? aCoordSequence.second(): aErrorLocation;
  CoordSequence::Iterator from = isFirsCoord? aCoordSequence.begin(): --CoordSequence::Iterator(aErrorLocation);
  CoordDelta moveDelta = *to - *from;
  CoordDelta betweenDelta(moveDelta.direction(), 1);
  Maybe<Draught> toDraught = m_from.testSquare(*to);
  Maybe<Draught> betweenDraught = m_from.testSquare(*from + betweenDelta);

  if(aCoordSequence.count() < 2)
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorIncompleteCoordSequence));
  }
  else if(moved.isNothing() || moved().color() != m_color)
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorNoRequestedDraught));
  }
  else if(*aCoordSequence.begin() != *to && !toDraught.isNothing())
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorBusySquare));
  }
  else if(moveDelta.distance() == 1 && doesJumpExist())
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorJumpExist));
  }
  else if(moveDelta.distance() > 1 && betweenDraught.isNothing())
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorNothingToJumpOver));
  }
  else if(moveDelta.distance() > 1 && betweenDraught().color() == moved().color())
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorJumpOverSameColor));
  }
  else if(!moved().isKing() && RulesOfGame::BoardBounds::isKingLine(from->y(), moved().color()))
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorGetKingButMoveFurther));
  }
  else if(!RulesOfGame::MoveValidator::isValidDirection(*from, *to, moved().color(), moved().isKing()))
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorInWrongDirection));
  }
  else if(!noVariant() && moveDelta.distance() > 1)
  {
    move = Move(Engine::Error::Ptr(new Move::ErrorJumpExist));
  }

  return move;
}

CoordSequence AmericanCheckersPositionAnalyser::createCoordSequence(const Engine::Move &aMove)
{
  //TODO: below can be improved: if Board is the same no need to set it
  Color color = aMove.color();
  if(m_color != color || m_from != aMove.from())
  {
    setPosition(aMove.from(), color);
  }

  MoveList::iterator toIt = m_valid_moves.find(aMove);

  if(toIt == m_valid_moves.end())
  {
    //TODO: Need better error here
    throw Engine::Error();
  }

  CoordSequence ret;

  if(aMove.anyCoordSequence())
  {
    typedef std::vector<CoordSequenceToMoveMap::const_iterator> FoundSequences;
    FoundSequences foundSequences;
    foundSequences.reserve(m_seq_move_map.size());

    for(CoordSequenceToMoveMap::const_iterator it = m_seq_move_map.begin(); it != m_seq_move_map.end(); ++it)
    {
      if(it->second.first == toIt)
      {
        foundSequences.push_back(it);
      }
    }

    if(foundSequences.size() == 0)
    {
      //How could it be, a?
      //TODO: Need better error here
      throw Engine::Error();
    }

    int randomIndex = rand() % foundSequences.size();
    ret = foundSequences[randomIndex]->first;
  }
  else
  {
    for(CoordSequenceToMoveMap::const_iterator it = m_seq_move_map.begin(); it != m_seq_move_map.end(); ++it)
    {
      if(aMove.coordSequenceId() == it->second.second && it->second.first == toIt)
      {
        ret = it->first;
        break;
      }
    }
  }

  if(ret.count() < 2)
  {
    //How could it be, a?
    //TODO: Need better error here
    throw Engine::Error();
  }

  return ret;
}

const PositionAnalyser::MoveList & AmericanCheckersPositionAnalyser::validMoves() const
{
  return m_valid_moves;
}

bool AmericanCheckersPositionAnalyser::doesJumpExist() const
{
  return validMoves().size() > 0 && validMoves().begin()->score() > 0;
}

void AmericanCheckersPositionAnalyser::reset()
{
    m_valid_moves.clear();
    m_seq_move_map.clear();
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

void AmericanCheckersPositionAnalyser::safeColorUpdate(const Engine::Coord &aDraughtCoord)
{
  Maybe<Draught> moved = m_from.testSquare(aDraughtCoord);

  if(!moved.isNothing())
  {
    updateValidMovesIfNeeded(moved().color());
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

      if(doesJumpExist())
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

        if(!doesJumpExist())
        {
          reset();
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
    addValidMove(aAccum, aBoard);
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

        addValidMove(CoordSequence(aDraught.coord(), moveToCoord), testBoard);
      }
    }
    catch(Coord::ErrorIntWrongCoord e)
    {
      continue;
    }
  }
}

void AmericanCheckersPositionAnalyser::addValidMove(const Engine::CoordSequence &aCoordSequence, const Engine::Board &aTo)
{
  MoveListInsertResult moveListIR = m_valid_moves.insert(Move(m_from, aTo));
  CoordSequenceToMoveMapInsertResult csToMoveMapIR =
        m_seq_move_map.insert(CoordSequenceToMoveMap::value_type(aCoordSequence, MoveCoordSequenceIdPair(moveListIR.first, 0)));

  if(!csToMoveMapIR.second)
  {
    //How could it be, a?
    //TODO: better error here?
    throw Engine::Error();
  }

  if(!moveListIR.second)
  {
    CoordSequenceToMoveMap::iterator current = csToMoveMapIR.first;

    CoordSequenceToMoveMap::iterator it = current;
    while(it != m_seq_move_map.begin())
    {
      --it;

      if(it->second.first == moveListIR.first)
      {
        ++(current->second.second);
      }
    }

    it = current;
    for(++it; it != m_seq_move_map.end(); ++it)
    {
      if(it->second.first == moveListIR.first)
      {
        ++(it->second.second);
      }
    }
  }
}

void AmericanCheckersPositionAnalyser::initSearchFilter()
{
  if(stepCount() < 0)
  {
    SearchMap zeroMap;

    for(CoordSequenceToMoveMap::const_iterator it = m_seq_move_map.begin(); it != m_seq_move_map.end(); ++it)
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

const Move & AmericanCheckersPositionAnalyser::foundMove() const
{
  if(!isFound())
    throw Engine::Error();

  return *(lastStep()->begin()->second->second.first);
}

const CoordSequence & AmericanCheckersPositionAnalyser::foundSequence() const
{
  if(!isFound())
    throw Engine::Error();

  return lastStep()->begin()->second->first;
}

int AmericanCheckersPositionAnalyser::foundCoordSequenceId() const
{
  if(!isFound())
    throw Engine::Error();

  return lastStep()->begin()->second->second.second;
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
