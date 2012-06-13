#include "AmericanCheckersPositionAnalyser.h"
#include "Move.h"
#include "RulesOfGame.h"
#include "CoordDelta.h"

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

Move AmericanCheckersPositionAnalyser::createMove(const Engine::CoordSequence &aCoordSequence, bool aUpdateColorIfNeeded)
{
  Board to(m_from);
  Move move;

  if(!safeColorUpdate(*aCoordSequence.begin(), aUpdateColorIfNeeded))
  {
    //TODO it is handled in findInValidMoves
    move = Move(Engine::Error::Ptr(new Move::ErrorNoRequestedDraught));
  }
  else
  {
    move = findInValidMoves(aCoordSequence);
  }

  return move;
}

Move AmericanCheckersPositionAnalyser::findInValidMoves(const Engine::CoordSequence &aCoordSequence)
{
  Board to(m_from); //TODO remove after refactoring
  Move move;

  bool temp_ret_flag = false;

  initSearchFilter();

  CoordSequence::Iterator it = aCoordSequence.begin();
  for(; it != aCoordSequence.end() && !noVariant(); ++it)
  {
    bool isLastCoord = (it == aCoordSequence.last());

    if(doSearchStep(it) && isLastCoord && stepCount() == foundSequence().count())
    {
      move = Move(m_from, fountTo());
      temp_ret_flag = true;
    }
  }

  if(!temp_ret_flag)
  {
    //TODO optimization required
    --it;
    Maybe<Draught> moved = m_from.testSquare(*aCoordSequence.begin());
    Maybe<Draught> movedTo = m_from.testSquare(*aCoordSequence.last());
    bool isFirsCoord = (it == aCoordSequence.begin());
    CoordSequence::Iterator to = isFirsCoord? aCoordSequence.second(): it;
    CoordSequence::Iterator from = isFirsCoord? aCoordSequence.begin(): --CoordSequence::Iterator(it);
    CoordDelta moveDelta = *to - *from;
    CoordDelta betweenDelta(moveDelta.direction(), 1);
    Maybe<Draught> toDraught = m_from.testSquare(*to);
    Maybe<Draught> betweenDraught = m_from.testSquare(*from + betweenDelta);
    //bool isLastCoord = (it == aCoordSequence.last());

    if(moved.isNothing() || moved().color() != m_color)
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorNoRequestedDraught));
      temp_ret_flag = true;
    }
    else if(aCoordSequence.count() < 2)
    {
      //TODO choose better error here
      move = Move(Engine::Error::Ptr(new Move::ErrorUnknown));
      temp_ret_flag = true;
    }
    else if(*aCoordSequence.begin() != *aCoordSequence.last() && !movedTo.isNothing())
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorToBusySquare));
      temp_ret_flag = true;
    }
    else if(*aCoordSequence.begin() != *to && !toDraught.isNothing())
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorJumpOverBusySquare));
      temp_ret_flag = true;
    }
    else if(moveDelta.distance() == 1 && validMoves().begin()->score() > 0) //TODO: optimize this
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorJumpExist));
      temp_ret_flag = true;
    }
    else if(moveDelta.distance() > 1 && betweenDraught.isNothing())
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorNothingToJumpOver));
      temp_ret_flag = true;
    }
    else if(moveDelta.distance() > 1 && betweenDraught().color() == moved().color())
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorJumpOverSameColor));
      temp_ret_flag = true;
    }
    else if(!moved().isKing() && RulesOfGame::BoardBounds::isKingLine(from->y(), moved().color()))
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorGetKingButMoveFurther));
      temp_ret_flag = true;
    }
    else if(!RulesOfGame::MoveValidator::isValidDirection(*from, *to, moved().color(), moved().isKing()))
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorInWrongDirection));
      temp_ret_flag = true;
    }
    else if(!noVariant() && moveDelta.distance() > 1)
    {
      move = Move(Engine::Error::Ptr(new Move::ErrorJumpExist));
      temp_ret_flag = true;
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

bool AmericanCheckersPositionAnalyser::safeColorUpdate(const Engine::Coord &aDraughtCoord, bool aUpdateColorIfNeeded)
{
  Maybe<Draught> moved = m_from.testSquare(aDraughtCoord);

  bool ret = !moved.isNothing() && (aUpdateColorIfNeeded || m_color == moved().color());

  if(ret && aUpdateColorIfNeeded)
  {
    updateValidMovesIfNeeded(moved().color());
  }

  return ret;
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
