#ifndef H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
#define H_AMERICAN_CHECKERS_POSITION_ANALYSER_H

#include "PositionAnalyser.h"
#include "Board.h"
#include "Color.h"

#include <set>
#include <map>


namespace Checkers
{
  namespace Engine
  {
    class AmericanCheckersPositionAnalyser: public PositionAnalyser
    {
    private:
      typedef std::set<Engine::Board> BoardStorage;
      typedef std::pair<BoardStorage::iterator, bool> BSInsertResult;

      typedef std::map<Engine::CoordSequence, BoardStorage::const_iterator> CoordSequenceToBoardMap;

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

    private:
      Board m_from;
      Color m_color;
      MoveList m_valid_moves;
      BoardStorage m_tos;
      CoordSequenceToBoardMap m_seq_board_map;
      bool m_jump_found;
    };
  };
};

#endif //H_AMERICAN_CHECKERS_POSITION_ANALYSER_H
