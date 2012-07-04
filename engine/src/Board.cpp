#include "Board.h"
#include "Coord.h"
#include "Color.h"
#include "Draught.h"
#include "RulesOfGame.h"
#include "BoardTraits.h"


namespace Checkers
{
  namespace Engine
  {
    class AnyColor : public Color
    {
    public:
     AnyColor() : Color(EBlack) {}
    };

    class AnyColorDraught : public Draught
    {
    public:
      AnyColorDraught(const Engine::Coord &aCoord) : Draught(aCoord, AnyColor()) {}
    };
  }
}

using namespace Checkers::Engine;



Board::Board()
  : m_draught_set()
{
}

Board::Board(const Engine::Board &aBoard)
  : m_draught_set(aBoard.m_draught_set)
{
}

bool Board::put(const Engine::Draught &aDraught)
{
  const BoardTraits &boardTraits = RulesOfGame::boardTraits();
  bool ret = aDraught.isKing() || boardTraits.canPutManOnKingRow() || !boardTraits.isKingRow(aDraught.coord().y(), aDraught.color());

  if(ret)
    ret = m_draught_set.insert(aDraught).second;

  return ret;
}

Maybe<Draught> Board::takeDraught(const Engine::Coord &aCoord)
{
  return getDraught(aCoord, false);
}

Maybe<Draught> Board::testSquare(const Engine::Coord &aCoord) const
{
  return getDraught(aCoord, true);
}

Maybe<Draught> Board::getDraught(const Engine::Coord &aCoord, bool aKeepOnBoard) const
{
  Maybe<Draught> ret;
  Iterator foundDraught = m_draught_set.find(AnyColorDraught(aCoord));
  if(foundDraught != m_draught_set.end())
  {
    ret = *foundDraught;

    if(!aKeepOnBoard)
      const_cast<DraughtSet*>(&m_draught_set)->erase(foundDraught);
  }
  return ret;
}
int Board::count() const
{
  return m_draught_set.size();
}

int Board::count(const Engine::Color aColor) const
{
  int draughtCount = 0;
  for(Iterator it = begin(); it != end(); ++it)
    if(it->color() == aColor)
      ++draughtCount;
  return draughtCount;
}

Board & Board::operator=(const Engine::Board &aBoard)
{
  m_draught_set = aBoard.m_draught_set;
  return *this;
}

Board::Ord Board::compare(const Engine::Board &aBoard) const
{
  if(count() < aBoard.count()) return ELess;
  if(count() > aBoard.count()) return EBigger;

  Ord ret = EEqual;

  for(Iterator itThis = begin(), itThat = aBoard.begin(); itThis != end(); ++itThis, ++itThat)
    if(*itThis != *itThat)
    {
      if((*itThis < *itThat)
         || ((itThis->coord() == itThat->coord())
             && ((itThis->color() == Color::EBlack && itThat->color() == Color::EWhite)
                 || (itThis->color() == itThat->color() && !itThis->isKing() && itThat->isKing()))))
        ret = ELess;
      else
        ret = EBigger;

      break;
    }

  return ret;
}

bool Board::operator==(const Engine::Board &aBoard) const
{
  return (EEqual == compare(aBoard));
}

bool Board::operator!=(const Engine::Board &aBoard) const
{
  return (EEqual != compare(aBoard));
}

bool Board::operator<(const Engine::Board &aBoard) const
{
  return (ELess == compare(aBoard));
}

bool Board::operator>(const Engine::Board &aBoard) const
{
  return (EBigger == compare(aBoard));
}

Board::Iterator Board::begin() const
{
  return m_draught_set.begin();
}

Board::Iterator Board::end() const
{
  return m_draught_set.end();
}
