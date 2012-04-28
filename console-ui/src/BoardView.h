#ifndef H_BOARD_VIEW_H
#define H_BOARD_VIEW_H

#include "AbstractView.h"


namespace Checkers
{
  namespace Engine
  {
    class Board;
  }

  namespace ConsoleUi
  {
    class BoardView : public AbstractView
    {
    public:
      enum Rotation
      {
        ERotation0
      , ERotation180
      };

    public:
      BoardView();
      BoardView(const Engine::Board &aBoard, Rotation aRotation = ERotation0);

      void setBoard(const Engine::Board &aBoard);

      Rotation rotation() const;
      void setRotation(Rotation aRotation);

    private:
      virtual std::string flushLine(int aN);
      char draughtView(int i, int j) const;
      char emptySquareView(int i, int j) const;

    private:
      const Engine::Board *m_Board;
      Rotation m_Rotation;
    };

    std::ostream & operator<<(std::ostream &aOut, const Engine::Board &aBoard);
  };
};

#endif //H_BOARD_VIEW_H
