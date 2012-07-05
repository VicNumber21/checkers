#include "JustOwnMoveAheadMind.h"
#include "RulesOfGame.h"
#include "PositionAnalyser.h"
#include "GameManager.h"

#include <stdlib.h>

using namespace Checkers::Engine;


JustOwnMoveAheadMind::Ptr JustOwnMoveAheadMind::create()
{
  JustOwnMoveAheadMind::Ptr self(new JustOwnMoveAheadMind);
  self->setSelf(self);
  return self;
}

JustOwnMoveAheadMind::JustOwnMoveAheadMind()
{
}

void JustOwnMoveAheadMind::thinkOfMove(MoveReceiver::Ptr aPtr)
{
  if(isReadyToGo())
    throw JustOwnMoveAheadMind::Error();

  m_move_receiver = aPtr;
  readyToGo();
}

//TODO: move into better MoveList implementation once
static const Move &chooseRandomly(const PositionAnalyser::MoveList &aMoveList)
{
  int choosenMoveIndex = rand() % aMoveList.size();

  PositionAnalyser::MoveList::const_iterator choosenMove = aMoveList.begin();

  while(choosenMoveIndex--)
    ++choosenMove;

  return *choosenMove;
}

void JustOwnMoveAheadMind::doStep()
{
  if(!m_move_receiver.expired())
  {
    MoveReceiver::StrongPtr moveReceiver = m_move_receiver.lock();

    const PositionAnalyser::MoveList &validMoves =
                  RulesOfGame::positionAnalyser().validMoves(GameManager::instance().currentBoard(), moveReceiver->color());

    //TODO in some games it is ok to miss the turn so it shall be better condition to throw or don't
    if(validMoves.size() == 0)
      throw JustOwnMoveAheadMind::Error();

    PositionAnalyser::MoveList::const_iterator it = validMoves.begin();
    int bestScore = it->score();
    PositionAnalyser::MoveList bestScoreMoves;

    if(bestScore > 0)
    {
      do
      {
        if(bestScore < it->score())
        {
          bestScoreMoves.clear();
          bestScoreMoves.insert(*it);
          bestScore = it->score();
        }
        else if(bestScore > 1 && bestScore == it->score())
        {
          bestScoreMoves.insert(*it);
        }

        ++it;
      }
      while(it != validMoves.end());
    }

    moveReceiver->set(chooseRandomly(bestScore < 2? validMoves: bestScoreMoves));
  }

  m_move_receiver.reset();
  sleep();
}
