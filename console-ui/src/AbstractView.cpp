#include "AbstractView.h"


std::ostream & Checkers::ConsoleUi::operator<<(std::ostream &aOut, AbstractView &aView)
{
  return aOut << aView.flushWhole();
}

