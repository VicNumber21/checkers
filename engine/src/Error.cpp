#include "Error.h"

using namespace Checkers::Engine;


void Error::raise() const
{
  throw *this;
}

const char * Error::what() const throw()
{
  return toString().c_str();
}

std::string Error::toString() const
{
  return std::string("Engine::Error");
}
