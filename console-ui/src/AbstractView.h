#ifndef H_ABSTRACT_VIEW_H
#define H_ABSTRACT_VIEW_H

#include <string>


namespace Checkers
{
  namespace ConsoleUi
  {
    class AbstractView
    {
    public:
      AbstractView();

      virtual std::string firstLine();
      virtual std::string nextLine();
      virtual std::string flushWhole();

    protected:
      virtual std::string flushLine(int aN) = 0;

    private:
      int m_CurrentLine;
    };

    std::ostream & operator<<(std::ostream &aOut, AbstractView &aView);
  };
};

#endif //H_ABSTRACT_VIEW_H
