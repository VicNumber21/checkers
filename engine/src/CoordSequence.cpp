#include "CoordSequence.h"
#include "RulesOfGame.h"
#include "PositionAnalyser.h"

using namespace Checkers::Engine;


CoordSequence::Error::Error(const CoordSequence::CoordList &aCoordList)
  : m_coord_list(aCoordList)
{
}

CoordSequence::CoordSequence()
{
}

CoordSequence::CoordSequence(const Engine::Coord &aStart, const Engine::Coord &aNext)
{
  m_coord_list.push_front(aStart);
  append(aNext);
}

CoordSequence::CoordSequence(const Engine::CoordSequence &aCoordSequence)
  : m_coord_list(aCoordSequence.m_coord_list)
{
}

//TODO better to return bool rather than throw exception here
void CoordSequence::append(const Engine::Coord &aNext)
{
  m_coord_list.push_back(aNext);
  validateTail();
}

void CoordSequence::pop()
{
  m_coord_list.pop_back();
}

CoordSequence & CoordSequence::operator=(const Engine::CoordSequence &aCoordSequence)
{
  m_coord_list = aCoordSequence.m_coord_list;
  return *this;
}

bool CoordSequence::operator==(const Engine::CoordSequence &aCoordSequence) const
{
  return  (m_coord_list == aCoordSequence.m_coord_list);
}

bool CoordSequence::operator!=(const Engine::CoordSequence &aCoordSequence) const
{
  return !(*this == aCoordSequence);
}

//TODO add test for it
bool CoordSequence::operator<(const Engine::CoordSequence &aCoordSequence) const
{
  return (m_coord_list < aCoordSequence.m_coord_list);
}

int CoordSequence::count() const
{
  return m_coord_list.size();
}

CoordSequence::Iterator CoordSequence::begin() const
{
  return at(0);
}

CoordSequence::Iterator CoordSequence::second() const
{
  return at(1);
}

CoordSequence::Iterator CoordSequence::thirdFromEnd() const
{
  return at(-3);
}

CoordSequence::Iterator CoordSequence::secondFromEnd() const
{
  return at(-2);
}

CoordSequence::Iterator CoordSequence::last() const
{
  return at(-1);
}

CoordSequence::Iterator CoordSequence::end() const
{
  return m_coord_list.end();
}

CoordSequence::Iterator CoordSequence::at(int aI) const
{
  CoordSequence::Iterator ret = m_coord_list.end();

  if(aI < 0)
  {
    if(-count() <= aI)
    {
      for(int i = 0; i > aI; --i)
        --ret;
    }
  }
  else if(aI < count())
  {
    ret = m_coord_list.begin();
    for(int i = 0; i < aI; ++i)
      ++ret;
  }

  return ret;
}

//TODO rework it as the following:
//it shall use positionAnalyser SearchFilter and validate the current coord if
//the filter shows that some move(s) exist(s) for current coord sequence
//I will do this rework during work on Human Player
void CoordSequence::validateTail() const
{
  bool wrongSequence = false;

  if(count() > 2)
    wrongSequence = !RulesOfGame::positionAnalyser().isValidCoordSequence(*thirdFromEnd(), *secondFromEnd(), *last());
  else if(count() > 1)
    wrongSequence = !RulesOfGame::positionAnalyser().isValidCoordSequence(*secondFromEnd(), *last());

  if(wrongSequence)
  {
    throw CoordSequence::Error(m_coord_list);
  }
}
