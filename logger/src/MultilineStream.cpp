#include "MultilineStream.h"


std::ostream & operator<<(std::ostream &aOut, MultilineStream &aValue)
{
  return aOut << aValue.m_buffer.str();
}

static bool putLine(std::ostream &aOut, std::istream &aIn)
{
  const std::streamsize tempBufferSize = 256;
  char tempBuffer[tempBufferSize];
  bool ret = false;

  do
  {
    aIn.getline(tempBuffer, tempBufferSize);

    if(aIn.eof() || aIn.bad())
      break;

    aOut << tempBuffer;
    ret = true;
  }
  while(aIn.fail());

  return ret;
}

MultilineStream & MultilineStream::operator<<(std::ostream& (*aManip)(std::ostream&))
{
  m_buffer << aManip;
  return *this;
}

MultilineStream & MultilineStream::operator<<(std::ios& (*aManip)(std::ios&))
{
  m_buffer << aManip;
  return *this;
}

MultilineStream & MultilineStream::operator<<(std::ios_base& (*aManip)(std::ios_base&))
{
  m_buffer << aManip;
  return *this;
}

MultilineStream & MultilineStream::operator<<(MultilineStream &aValue)
{
  return (*this) << aValue.m_buffer;
}

MultilineStream & MultilineStream::operator<<(std::stringstream &aValue)
{
  std::stringstream result;

  while(!(m_buffer.eof() && aValue.eof()))
  {
    bool res = putLine(result, m_buffer);
    res = putLine(result, aValue) || res;

    if(res)
      result << std::endl;
  }

  m_buffer.str(result.str());

  return *this;
}
