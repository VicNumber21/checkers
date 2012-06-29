#include "Player.h"
#include "RulesOfGame.h"
#include "PositionAnalyser.h"

using namespace Checkers::Engine;


Player::Ptr Player::create(Color aColor, PlayerMind::Ptr aMind)
{
  Player::Ptr self(new Player(aColor, aMind));
  self->setSelf(self);
  return self;
}

Player::Player(Color aColor, PlayerMind::Ptr aMind)
  : m_mind(aMind)
  , m_color(aColor)
  , m_thinking(false)
  , m_ready_to_move(false)
{
}

void Player::setColor(Color aColor)
{
  throwIfActive();
  m_color = aColor;
}

Color Player::color() const
{
  return m_color;
}

void Player::setMind(PlayerMind::Ptr aMind)
{
  throwIfActive();
  m_mind = aMind;
}

void Player::yourTurn()
{
  throwIfActive();
  readyToGo();
}

bool Player::isThinking() const
{
  return m_thinking;
}

void Player::doStep()
{
  if(isReadyToMove())
    doMove();
  else if(!isThinking())
    think();

  sleep();
}

void Player::think()
{
  if(!m_mind.expired())
  {
    m_mind.lock()->thinkOfMove(self());
    m_thinking = true;
  }
}

void Player::doMove()
{
  //TODO applyMove to GameManager
  m_ready_to_move = false;
}

void Player::set(const Engine::CoordSequence &aCoordSequence)
{
  //TODO get current board from GameManager
  Board bCurrent;
  RulesOfGame::positionAnalyser().setPosition(bCurrent, color());
  Move move = RulesOfGame::positionAnalyser().createMove(aCoordSequence);
  set(move);
}

void Player::set(const Engine::Move &aMove)
{
  if(!isThinking() || isReadyToMove())
    throw Player::ErrorIsNotWaitingForMove();

  if(!aMove.isValid())
    aMove.error()->raise();

  if(aMove.color() != color())
    throw Player::ErrorWrongMoveColor();

  m_move = aMove;
  //TODO think about State pattern here
  m_thinking = false;
  m_ready_to_move = true;
}

bool Player::isReadyToMove() const
{
  return m_ready_to_move;
}

bool Player::isActive() const
{
  return isReadyToGo() || isThinking() || isReadyToMove();
}

void Player::throwIfActive() const
{
  if(isActive())
    throw Player::ErrorIsActive();
}
