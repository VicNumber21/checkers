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

void RandomChoiceMind::thinkOfMove(Checkers::Engine::MoveReceiver::Ptr aPtr)
{
  if(isReadyToGo())
    throw RandomChoiceMind::Error();

  m_move_receiver = aPtr;
  readyToGo();
}

void RandomChoiceMind::doStep()
{
  if(!m_move_receiver.expired())
  {
    MoveReceiver::StrongPtr moveReceiver = m_move_receiver.lock();

    const PositionAnalyser::MoveList &validMoves =
                  RulesOfGame::positionAnalyser().validMoves(GameManager::instance().currentBoard(), moveReceiver->color());

    if(validMoves.size() == 0)
      throw RandomChoiceMind::Error();

    int choosenMoveIndex = rand() % validMoves.size();

    PositionAnalyser::MoveList::const_iterator choosenMove = validMoves.begin();

    while(choosenMoveIndex--)
      ++choosenMove;

    moveReceiver->set(*choosenMove);
  }

  m_move_receiver.reset();
  sleep();
}
