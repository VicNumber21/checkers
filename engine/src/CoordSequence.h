#ifndef H_COORD_SEQUENCE_H
#define H_COORD_SEQUENCE_H

#include "Coord.h"

#include <list>


namespace Checkers
{
  namespace Engine
  {
    class CoordSequence
    {
    public:
      typedef std::list<Engine::Coord> CoordList;
      typedef CoordList::const_iterator Iterator;

      class Error
      {
      public:
        Error(const CoordSequence::CoordList &aCoordList);

      public:
        CoordSequence::CoordList m_coord_list;
      };

    public:
      CoordSequence();
      CoordSequence(const Engine::Coord &aStart, const Engine::Coord &aNext);
      CoordSequence(const Engine::CoordSequence &aCoordSequence);

      void append(const Engine::Coord &aNext);
      void pop();

      CoordSequence & operator=(const Engine::CoordSequence &aCoordSequence);

      bool operator==(const Engine::CoordSequence &aCoordSequence) const;
      bool operator!=(const Engine::CoordSequence &aCoordSequence) const;

      int count() const;

      CoordSequence::Iterator begin() const;
      CoordSequence::Iterator second() const;
      CoordSequence::Iterator thirdFromEnd() const;
      CoordSequence::Iterator secondFromEnd() const;
      CoordSequence::Iterator last() const;
      CoordSequence::Iterator end() const;

    private:
      CoordSequence::Iterator at(int aI) const;
      void validateTail() const;

    private:
      CoordList m_coord_list;
    };
  };
};

#endif //H_COORD_SEQUENCE_H
