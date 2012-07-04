#include "PlayerTests.h"
#include "PlayerTestsMocs.h"
#include "RulesOfGameManager.h"
#include "RulesOfGameInstances.h"
#include "Player.h"
#include "GameManager.h"
#include "Iteration.h"
#include "RandomChoiceMind.h"
#include "PrettyPrint.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( PlayerTests );

Board afterFirstMoveBoard()
{
  Board b;

  for(int i = 0; i < 3*8/2; ++i)
  {
    int rowBlack = i / 4;
    int rowWhite = rowBlack + 5;
    int colBlack = (i % 4) * 2;
    int colWhite = colBlack + 1;

    if(rowBlack % 2 == 1)
      std::swap(colBlack, colWhite);

    if(rowBlack == 2 && colBlack == 0)
      b.put(Draught(Coord('b', '4'), Color::EBlack));
    else
      b.put(Draught(Coord(colBlack, rowBlack), Color::EBlack));

    b.put(Draught(Coord(colWhite, rowWhite), Color::EWhite));
  }

  return b;
}

void PlayerTests::setUp()
{
  RulesOfGameManager::instance().append(RulesOfGameInstanceInterface::Ptr(new AmericanCheckersRulesOfGame), true);
  GameManager::instance().setCurrentBoard();
}

void PlayerTests::tearDown()
{
  RulesOfGameManager::instance().reset();
}

void PlayerTests::thinkAndMakeMove()
{
  IKnowThreeMoveMind::Ptr stupidMind = IKnowThreeMoveMind::create();
  Player::Ptr players[2] = {Player::create(Color::EBlack, stupidMind), Player::create(Color::EWhite, stupidMind)};

  stupidMind->registerForNextIteration(false);
  players[0]->registerForNextIteration(false);
  players[1]->registerForNextIteration(false);

  int activePlayerIndex = 0;
  players[0]->yourTurn();

  int cycleCount = 0;

  while(stupidMind->doesKnowAnythingElse())
  {
    Loop::Iteration::instance().walk();

    if(players[activePlayerIndex]->isDone())
    {
      activePlayerIndex = (activePlayerIndex + 1) % 2;
      players[activePlayerIndex]->yourTurn();
    }

    CPPUNIT_ASSERT(cycleCount < 13);
    ++cycleCount;
  }

  CPPUNIT_ASSERT_EQUAL(13, cycleCount);
}

void PlayerTests::stepByStep()
{
  RemoteControlMind::Ptr remoteControlMind = RemoteControlMind::create();
  Player::Ptr player = Player::create(Color::EBlack, remoteControlMind);

  remoteControlMind->registerForNextIteration(false);
  player->registerForNextIteration(false);

  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(player->isDone());
  CPPUNIT_ASSERT_EQUAL(0, remoteControlMind->count());

  player->yourTurn();

  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(!player->isDone());
  CPPUNIT_ASSERT_THROW(player->setColor(Color::EWhite), Player::ErrorIsActive);
  CPPUNIT_ASSERT_THROW(player->yourTurn(), Player::ErrorIsActive);
  CPPUNIT_ASSERT_EQUAL(0, remoteControlMind->count());

  Loop::Iteration::instance().walk();

  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(!player->isDone());
  CPPUNIT_ASSERT(remoteControlMind->requestedColor() == Color::EBlack);
  CPPUNIT_ASSERT_THROW(player->setColor(Color::EWhite), Player::ErrorIsActive);
  CPPUNIT_ASSERT_THROW(player->yourTurn(), Player::ErrorIsActive);
  CPPUNIT_ASSERT_EQUAL(1, remoteControlMind->count());

  remoteControlMind->removeFromIteration();
  Loop::Iteration::instance().walk();
  CPPUNIT_ASSERT_EQUAL(1, remoteControlMind->count());
  remoteControlMind.reset();

  CPPUNIT_ASSERT(!player->hasMind());
  CPPUNIT_ASSERT(player->isDone());

  remoteControlMind = RemoteControlMind::create();
  remoteControlMind->registerForNextIteration(false);
  player->setMind(remoteControlMind);

  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(!player->isDone());
  CPPUNIT_ASSERT(remoteControlMind->requestedColor() == Color::EBlack);
  CPPUNIT_ASSERT_THROW(player->setColor(Color::EWhite), Player::ErrorIsActive);
  CPPUNIT_ASSERT_THROW(player->yourTurn(), Player::ErrorIsActive);
  CPPUNIT_ASSERT_EQUAL(0, remoteControlMind->count());

  Loop::Iteration::instance().walk();

  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(!player->isDone());
  CPPUNIT_ASSERT(remoteControlMind->requestedColor() == Color::EBlack);
  CPPUNIT_ASSERT_THROW(player->setColor(Color::EWhite), Player::ErrorIsActive);
  CPPUNIT_ASSERT_THROW(player->yourTurn(), Player::ErrorIsActive);
  CPPUNIT_ASSERT_EQUAL(1, remoteControlMind->count());

  remoteControlMind->setMove(CoordSequence(Coord('b', '6'), Coord('c', '5')));

  CPPUNIT_ASSERT_THROW(Loop::Iteration::instance().walk(), Player::ErrorWrongMoveColor);
  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(!player->isDone());
  CPPUNIT_ASSERT(remoteControlMind->requestedColor() == Color::EBlack);
  CPPUNIT_ASSERT_THROW(player->setColor(Color::EWhite), Player::ErrorIsActive);
  CPPUNIT_ASSERT_THROW(player->yourTurn(), Player::ErrorIsActive);
  CPPUNIT_ASSERT_EQUAL(2, remoteControlMind->count());

  remoteControlMind->setMove(CoordSequence(Coord('a', '3'), Coord('b', '4')));

  Loop::Iteration::instance().walk();

  CPPUNIT_ASSERT_EQUAL(afterFirstMoveBoard(), GameManager::instance().currentBoard());
  CPPUNIT_ASSERT_THROW(remoteControlMind->setMoveTest(CoordSequence(Coord('a', '3'), Coord('b', '4'))), Player::ErrorIsNotWaitingForMove);
  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(player->isDone());
  CPPUNIT_ASSERT_NO_THROW(player->setColor(Color::EWhite));
  CPPUNIT_ASSERT_NO_THROW(player->yourTurn());
  CPPUNIT_ASSERT_EQUAL(3, remoteControlMind->count());

  CPPUNIT_ASSERT(player->hasMind());
  CPPUNIT_ASSERT(!player->isDone());
  CPPUNIT_ASSERT_THROW(player->setColor(Color::EBlack), Player::ErrorIsActive);
  CPPUNIT_ASSERT_THROW(player->yourTurn(), Player::ErrorIsActive);
  CPPUNIT_ASSERT_EQUAL(3, remoteControlMind->count());
  CPPUNIT_ASSERT(remoteControlMind->requestedColor() == Color::EWhite);
}

void playToWin(PlayerMind::Ptr aBlackMind, PlayerMind::Ptr aWhiteMind, bool aVerbose)
{
  Player::Ptr player = Player::create(Color::EBlack, aBlackMind);

  player->registerForNextIteration(false);

  player->yourTurn();

  int cycleCount = 0;
  int moveCount = 1;

  if (aVerbose) std::cerr << std::endl << "Game start:";
  if (aVerbose) std::cerr << GameManager::instance().currentBoard();
  if (aVerbose) std::cerr << std::endl << "=====================";
  if (aVerbose) std::cerr << std::endl << "Move " << moveCount;

  while(GameManager::instance().currentBoard().count(player->color()) != 0)
  {
    Loop::Iteration::instance().walk();

    if(player->isDone())
    {
      if (aVerbose) std::cerr << GameManager::instance().currentBoard();
      player->setColor(player->color() == Color::EBlack? Color::EWhite: Color::EBlack);
      player->setMind(player->color() == Color::EBlack? aBlackMind: aWhiteMind);
      player->yourTurn();
      cycleCount = 0;

      if(player->color() == Color::EBlack)
      {
        ++moveCount;
        if (aVerbose) std::cerr << std::endl << "=====================";
        if (aVerbose) std::cerr << std::endl << "Move " << moveCount;
      }
    }

    CPPUNIT_ASSERT(cycleCount < 5);
    ++cycleCount;
    CPPUNIT_ASSERT(moveCount < 500);
  }

  if (aVerbose) std::cerr << std::endl << "=====================";
  if (aVerbose) std::cerr << std::endl << (player->color() == Color::EBlack? "White" : "Black") << " player won!";
}

void PlayerTests::randomChoiceMind()
{
  RandomChoiceMind::Ptr randomChoiceMind = RandomChoiceMind::create();
  randomChoiceMind->registerForNextIteration(false);

  playToWin(randomChoiceMind, randomChoiceMind, false);
}
