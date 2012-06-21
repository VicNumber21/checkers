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

      typedef std::pair<MoveList::iterator, int> MoveCoordSequenceIdPair;
      typedef std::map<Engine::CoordSequence, MoveCoordSequenceIdPair> CoordSequenceToMoveMap;
      typedef std::pair<CoordSequenceToMoveMap::iterator, bool> CoordSequenceToMoveMapInsertResult;

      typedef IteratorLess<CoordSequence::Iterator> CoordSequenceIteratorLess;
      typedef std::multimap<CoordSequence::Iterator, CoordSequenceToMoveMap::const_iterator, CoordSequenceIteratorLess> SearchMap;
      typedef std::list<SearchMap> SearchFilter;

    public:
      AmericanCheckersPositionAnalyser();

      virtual void setPosition(const Engine::Board &aBoard, const Engine::Color &aColor = Engine::Color(Color::EBlack));

      virtual Engine::Move createMove(const Engine::CoordSequence &aCoordSequence, bool aUpdateColorIfNeeded = true);

      virtual Engine::CoordSequence createCoordSequence(const Engine::Move &aMove, const Engine::Color &aColor);

      virtual const MoveList &validMoves() const;

    protected:
      void reset();
      void updateValidMovesIfNeeded(const Engine::Color &aColor, bool aForced = false);
      void safeColorUpdate(const Engine::Coord &aDraughtCoord);
      Engine::Move findInValidMoves(const Engine::CoordSequence &aCoordSequence);
      void searchForValidMoves();
      void searchForJumps(CoordSequence &aAccum, const Engine::Board &aBoard, const Engine::Draught &aDraught, bool aGotKing);
      void searchForSimpleMoves(const Engine::Board &aBoard, const Engine::Draught &aDraught);
      void addValidMove(const Engine::CoordSequence &aCoordSequence, const Engine::Board &aTo);
      bool doesJumpExist() const;
      Engine::Move createErrorMove(const Engine::CoordSequence &aCoordSequence, const Engine::CoordSequence::Iterator &aErrorLocation) const;

      void initSearchFilter();
      void backToZeroStep();
      void searchReset();
      bool doSearchStep(const Engine::CoordSequence::Iterator &aCoordI);
      void undoSearchStep();
      bool isFound() const;
      bool noVariant() const;
      const Engine::Move &foundMove() const;
      const Engine::CoordSequence &foundSequence() const;
      int foundCoordSequenceId() const;
      SearchFilter::const_iterator lastStep() const;
      int stepCount() const;

    private:
      Board m_from;
      Color m_color;
      MoveList m_valid_moves;
      CoordSequenceToMoveMap m_seq_move_map;
      //TODO: Move to another class probably
      SearchFilter m_search_filter;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
