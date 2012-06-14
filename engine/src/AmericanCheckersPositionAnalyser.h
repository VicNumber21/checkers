#ifndef H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
#define H_AMERICAN_CHECKERS_POSITION_ANALYSER_H

#include "PositionAnalyser.h"
#include "Board.h"
#include "Color.h"
#include "CoordSequence.h"

#include <set>
#include <map>
#include <list>

namespace Checkers
{
  namespace Engine
  {
    class AmericanCheckersPositionAnalyser: public PositionAnalyser
    {
    private:
      template <class T>
      class IteratorLess : public std::binary_function<T, T, bool>
      {
      public:
        bool operator()(const T &aFirst, const T &aSecond) const
        {
          return (*aFirst) < (*aSecond);
        }
      };

      typedef std::pair<MoveList::iterator, bool> MoveListInsertResult;

      typedef std::map<Engine::CoordSequence, MoveList::const_iterator> CoordSequenceToMoveMap;

      typedef IteratorLess<CoordSequence::Iterator> CoordSequenceIteratorLess;
      typedef std::multimap<CoordSequence::Iterator, CoordSequenceToMoveMap::const_iterator, CoordSequenceIteratorLess> SearchMap;
      typedef std::list<SearchMap> SearchFilter;

    public:
      AmericanCheckersPositionAnalyser();

      virtual void setPosition(const Engine::Board &aBoard, const Engine::Color &aColor = Engine::Color(Color::EBlack));

      virtual Engine::Move createMove(const Engine::CoordSequence &aCoordSequence, bool aUpdateColorIfNeeded = true);

      virtual const MoveList &validMoves();

    protected:
      void reset();
      void updateValidMovesIfNeeded(const Engine::Color &aColor, bool aForced = false);
      bool safeColorUpdate(const Engine::Coord &aDraughtCoord, bool aUpdateColorIfNeeded);
      Engine::Move findInValidMoves(const Engine::CoordSequence &aCoordSequence);
      void searchForValidMoves();
      void searchForJumps(CoordSequence &aAccum, const Engine::Board &aBoard, const Engine::Draught &aDraught, bool aGotKing);
      void searchForSimpleMoves(const Engine::Board &aBoard, const Engine::Draught &aDraught);

      void initSearchFilter();
      void backToZeroStep();
      void searchReset();
      bool doSearchStep(const Engine::CoordSequence::Iterator &aCoordI);
      void undoSearchStep();
      bool isFound() const;
      bool noVariant() const;
      const Engine::Move &foundMove() const;
      const Engine::CoordSequence &foundSequence() const;
      SearchFilter::const_iterator lastStep() const;
      int stepCount() const;

    private:
      Board m_from;
      Color m_color;
      MoveList m_valid_moves;
      CoordSequenceToMoveMap m_seq_move_map;
      bool m_jump_found;
      //TODO: Move to another class probably
      SearchFilter m_search_filter;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
