#include "AmericanCheckersPositionAnalyser.h"
#include "Move.h"
#include "RulesOfGame.h"

using namespace Checkers::Engine;


AmericanCheckersPositionAnalyser::AmericanCheckersPositionAnalyser()
{
}

void AmericanCheckersPositionAnalyser::setPosition(const Engine::Board &aBoard)
{
  m_current_board = aBoard;
}

Move AmericanCheckersPositionAnalyser::createMove(const Engine::CoordSequence &aCoorsSequence) const
{
  Board to(m_current_board);
  Move move;

  try
  {
    ActionAtBoard::Ptr action = RulesOfGame::MoveValidator::transformIntoActions(m_current_board, aCoorsSequence);

    if(!action)
      throw Engine::Error::Ptr(new Move::ErrorUnknown);

    action->perform(to);
    move = Move(m_current_board, to);
  }
  catch(Engine::Error::Ptr e)
  {
    move = Move(e);
  }

  return move;
}

PositionAnalyser::MoveList AmericanCheckersPositionAnalyser::validMoves() const
{
  return m_valid_simple_moves.size() > 0? m_valid_simple_moves: m_valid_jumps;
}
