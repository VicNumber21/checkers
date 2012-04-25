#ifndef H_ABSTRACT_VIEW_H
#define H_ABSTRACT_VIEW_H

#include <string>


namespace Checkers
{
  namespace Engine
  {
    class Board;
  }

  namespace ConsoleUi
  {
    class AbstractView
    {
    public:
      virtual std::string firstLine() = 0;
      virtual std::string nextLine() = 0;
      virtual std::string flushWhole() = 0;
    };

    std::ostream & operator<<(std::ostream &aOut, AbstractView &aView);
  };
};

#endif //H_ABSTRACT_VIEW_H
