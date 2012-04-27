#include "AbstractView.h"

using namespace Checkers::ConsoleUi;


AbstractView::AbstractView()
  : m_CurrentLine(0)
{
}

std::string AbstractView::firstLine()
{
  m_CurrentLine = 0;
  return flushLine(m_CurrentLine);
}

std::string AbstractView::nextLine()
{
  return flushLine(++m_CurrentLine);
}

std::string AbstractView::flushWhole()
{
  std::string ret;

  for(std::string it = firstLine(); !it.empty(); it = nextLine())
  {
    ret += it += '\n';
  }

  return ret;
}

std::ostream & Checkers::ConsoleUi::operator<<(std::ostream &aOut, AbstractView &aView)
{
  return aOut << aView.flushWhole();
}

