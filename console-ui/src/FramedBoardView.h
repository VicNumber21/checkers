#ifndef H_FRAMED_BOARD_VIEW_H
#define H_FRAMED_BOARD_VIEW_H

#include "AbstractView.h"
#include "BoardView.h"


namespace Checkers
{
  namespace ConsoleUi
  {
    class FramedBoardView : public AbstractView
    {
    public:
      FramedBoardView();
      FramedBoardView(const Engine::Board &aBoard, BoardView::Rotation aRotation = BoardView::ERotation0);

      void setBoard(const Engine::Board &aBoard);

      BoardView::Rotation rotation() const;
      void setRotation(BoardView::Rotation aRotation);

    private:
      virtual std::string flushRow(int aN);
      std::string letterRow() const;
      std::string topBottomFrame() const;
      std::string framedRow(int aN);

    private:
      BoardView m_BoardView;
    };
  };
};

#endif //H_FRAMED_BOARD_VIEW_H
