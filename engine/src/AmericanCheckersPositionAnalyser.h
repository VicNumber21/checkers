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

      typedef std::set<Engine::Board> BoardStorage;
      typedef std::pair<BoardStorage::iterator, bool> BSInsertResult;

      typedef std::map<Engine::CoordSequence, BoardStorage::const_iterator> CoordSequenceToBoardMap;

      typedef IteratorLess<CoordSequence::Iterator> CoordSequenceIteratorLess;
      typedef std::multimap<CoordSequence::Iterator, CoordSequenceToBoardMap::const_iterator, CoordSequenceIteratorLess> SearchMap;
      typedef std::list<SearchMap> SearchFilter;

    public:
      AmericanCheckersPositionAnalyser();

      virtual void setPosition(const Engine::Board &aBoard, const Engine::Color &aColor = Engine::Color(Color::EBlack));

      virtual Engine::Move createMove(const Engine::CoordSequence &aCoorsSequence, bool aUpdateColorIfNeeded = true);

      virtual const MoveList &validMoves();

    protected:
      void reset();
      void updateValidMovesIfNeeded(const Engine::Color &aColor, bool aForced = false);
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
      const Engine::Board &fountTo() const;
      const Engine::CoordSequence &foundSequence() const;
      SearchFilter::const_iterator lastStep() const;
      int stepCount() const;

    private:
      Board m_from;
      Color m_color;
      MoveList m_valid_moves;
      BoardStorage m_tos;
      CoordSequenceToBoardMap m_seq_board_map;
      bool m_jump_found;
      //TODO: Move to another class probably
      SearchFilter m_search_filter;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
