#include "AbstractView.h"

using namespace Checkers::ConsoleUi;


AbstractView::AbstractView()
  : m_CurrentRow(0)
{
}

std::string AbstractView::firstRow()
{
  m_CurrentRow = 0;
  return flushRow(m_CurrentRow);
}

std::string AbstractView::nextRow()
{
  return flushRow(++m_CurrentRow);
}

std::string AbstractView::flushWhole()
{
  std::string ret;

  for(std::string it = firstRow(); !it.empty(); it = nextRow())
  {
    ret += it += '\n';
  }

  return ret;
}

std::ostream & Checkers::ConsoleUi::operator<<(std::ostream &aOut, AbstractView &aView)
{
  return aOut << aView.flushWhole();
}

