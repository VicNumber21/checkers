#ifndef H_MULTILINE_STREAM_H
#define H_MULTILINE_STREAM_H

#include <sstream>


//TODO it shall not be in logger in fact

class MultilineStream
{
  friend std::ostream & operator<<(std::ostream &aOut, MultilineStream &aValue);

public:
  MultilineStream();

  template<class T>
  MultilineStream & operator<<(const T &aValue)
  {
    m_buffer << aValue;
    clearFrame();
    return *this;
  }

  MultilineStream & operator<<(std::ostream& (*aManip)(std::ostream&));
  MultilineStream & operator<<(std::ios& (*aManip)(std::ios&));
  MultilineStream & operator<<(std::ios_base& (*aManip)(std::ios_base&));

  MultilineStream & operator<<(MultilineStream &aValue);
  MultilineStream & operator<<(std::stringstream &aValue);

  void makeFrame();
  void clearFrame();
  bool isFramed() const;

private:
  void rewind();

private:
  std::stringstream m_buffer;
  size_t m_line_count;
  size_t m_max_line_length;
};

#endif //H_MULTILINE_STREAM_H
