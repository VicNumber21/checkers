#ifndef H_KING_FLAG_H
#define H_KING_FLAG_H

namespace Checkers
{
  namespace Engine
  {
    template<class VT, int MASK>
    class BitFlag
    {
    public:
      bool operator()() const
      {
        return m_value & MASK;
      }

      void set(bool aFlag)
      {
        if(aFlag)
          m_value |= MASK;
        else
          m_value &= ~MASK;
      }

    private:
      VT m_value;
    };
  };
};

#endif //H_KING_FLAG_H
