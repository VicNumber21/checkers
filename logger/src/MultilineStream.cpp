#include "MultilineStream.h"


std::ostream & operator<<(std::ostream &aOut, MultilineStream &aValue)
{
  return aOut << aValue.m_buffer.str();
}

static std::string getLine(std::istream &aIn)
{
  const std::streamsize tempBufferSize = 256;
  char tempBuffer[tempBufferSize];
  std::string line;

  do
  {
    aIn.getline(tempBuffer, tempBufferSize);

    if(aIn.eof() || aIn.bad())
      break;

    line.append(tempBuffer);
  }
  while(aIn.fail());

  return line;
}

MultilineStream::MultilineStream()
  : m_line_count(0)
  , m_max_line_length(0)
{
}

MultilineStream & MultilineStream::operator<<(std::ostream& (*aManip)(std::ostream&))
{
  m_buffer << aManip;
  clearFrame();
  return *this;
}

MultilineStream & MultilineStream::operator<<(std::ios& (*aManip)(std::ios&))
{
  m_buffer << aManip;
  clearFrame();
  return *this;
}

MultilineStream & MultilineStream::operator<<(std::ios_base& (*aManip)(std::ios_base&))
{
  m_buffer << aManip;
  clearFrame();
  return *this;
}

MultilineStream & MultilineStream::operator<<(MultilineStream &aValue)
{
  (*this) << aValue.m_buffer;
  aValue.rewind();
  return (*this);
}

MultilineStream & MultilineStream::operator<<(std::stringstream &aValue)
{
  std::stringstream result;

  size_t newLineCount = 0;
  size_t newMaxLineLength = 0;

  while(!(m_buffer.eof() && aValue.eof()))
  {
    std::string myCurrentLine = getLine(m_buffer);
    std::string valueCurrentLine = getLine(aValue);

    if(myCurrentLine.size() + valueCurrentLine.size() > 0)
    {
      result << myCurrentLine;

      if(isFramed())
      {
        size_t delta = m_max_line_length - myCurrentLine.size();
        result << std::string(delta, ' ');

        ++newLineCount;

        size_t lineLength = m_max_line_length + valueCurrentLine.size();

        if(newMaxLineLength < lineLength)
          newMaxLineLength = lineLength;
      }

      result << valueCurrentLine;
      result << std::endl;
    }
  }

  if(isFramed())
  {
    m_line_count = newLineCount;
    m_max_line_length = newMaxLineLength;
  }

  m_buffer.str(result.str());
  rewind();

  return *this;
}

void MultilineStream::makeFrame()
{
  if(isFramed())
    return;

  while(!m_buffer.eof())
  {
    std::string counter = getLine(m_buffer);

    if(m_max_line_length < counter.size())
      m_max_line_length = counter.size();

    if(m_buffer.eof() || m_buffer.bad())
      break;

    ++m_line_count;
  }

  rewind();
}

void MultilineStream::clearFrame()
{
  m_line_count = 0;
  m_max_line_length = 0;
}

bool MultilineStream::isFramed() const
{
  return (m_line_count > 0 || m_max_line_length > 0);
}

void MultilineStream::rewind()
{
  m_buffer.clear();
  m_buffer.seekg(0, std::ios::beg);
}
