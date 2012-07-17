#ifndef H_MULTILINE_STREAM_H
#define H_MULTILINE_STREAM_H

#include <sstream>


//TODO it shall not be in logger in fact

class MultilineStream
{
  friend std::ostream & operator<<(std::ostream &aOut, MultilineStream &aValue);

public:
  template<class T>
  MultilineStream & operator<<(const T &aValue)
  {
    m_buffer << aValue;
    return *this;
  }

  MultilineStream & operator<<(std::ostream& (*aManip)(std::ostream&));
  MultilineStream & operator<<(std::ios& (*aManip)(std::ios&));
  MultilineStream & operator<<(std::ios_base& (*aManip)(std::ios_base&));

  MultilineStream & operator<<(MultilineStream &aValue);
  MultilineStream & operator<<(std::stringstream &aValue);

private:
  std::stringstream m_buffer;
};

#endif //H_MULTILINE_STREAM_H
