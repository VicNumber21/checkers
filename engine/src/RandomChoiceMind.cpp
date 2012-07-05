#include "RandomChoiceMind.h"
#include "RulesOfGame.h"
#include "PositionAnalyser.h"
#include "GameManager.h"

#include <stdlib.h>

using namespace Checkers::Engine;


RandomChoiceMind::Ptr RandomChoiceMind::create()
{
  RandomChoiceMind::Ptr self(new RandomChoiceMind);
  self->setSelf(self);
  return self;
}

RandomChoiceMind::RandomChoiceMind()
{
}

void RandomChoiceMind::thinkOfMove(MoveReceiver::Ptr aPtr)
{
  if(isReadyToGo())
    throw RandomChoiceMind::Error();

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

void RandomChoiceMind::doStep()
{
  if(!m_move_receiver.expired())
  {
    MoveReceiver::StrongPtr moveReceiver = m_move_receiver.lock();

    const PositionAnalyser::MoveList &validMoves =
                  RulesOfGame::positionAnalyser().validMoves(GameManager::instance().currentBoard(), moveReceiver->color());

    //TODO in some games it is ok to miss the turn so it shall be better condition to throw or don't
    if(validMoves.size() == 0)
      throw RandomChoiceMind::Error();

    moveReceiver->set(chooseRandomly(validMoves));
  }

  m_move_receiver.reset();
  sleep();
}
