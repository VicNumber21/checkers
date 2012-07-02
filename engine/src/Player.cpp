#include "Player.h"
#include "RulesOfGame.h"
#include "PositionAnalyser.h"
#include "GameManager.h"

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
  m_mind = aMind;

  if(isThinking())
    think();
}

void Player::yourTurn()
{
  throwIfActive();
  readyToGo();
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
  if(hasMind())
  {
    m_mind.lock()->thinkOfMove(self());
  }

  m_thinking = true;
  m_ready_to_move = false;
}

void Player::doMove()
{
  GameManager::instance().applyMove(m_move);
  m_move = Move();
  m_ready_to_move = false;
}

void Player::set(const Engine::CoordSequence &aCoordSequence)
{
  RulesOfGame::positionAnalyser().setPosition(GameManager::instance().currentBoard(), color());
  Move move = RulesOfGame::positionAnalyser().createMove(aCoordSequence);
  set(move);
}

void Player::set(const Engine::Move &aMove)
{
  if(!isThinking())
    throw Player::ErrorIsNotWaitingForMove();

  if(!aMove.isValid())
    aMove.error()->raise();

  if(aMove.color() != color())
    throw Player::ErrorWrongMoveColor();

  m_move = aMove;
  //TODO think about State pattern here
  m_thinking = false;
  m_ready_to_move = true;
  readyToGo();
}

bool Player::hasMind() const
{
  return !m_mind.expired();
}

bool Player::isThinking() const
{
  return hasMind() && m_thinking;
}

bool Player::isReadyToMove() const
{
  return m_ready_to_move;
}

bool Player::isDone() const
{
  return !isActive();
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
