#ifndef H_DRAUGHT_H
#define H_DRAUGHT_H

#include "ColorBase.h"
#include "CoordBase.h"
#include "BitFlag.h"


namespace Checkers
{
  namespace Engine
  {
    class Coord;
    class Color;

    class Draught
    {
    public:
      Draught(const Engine::Draught &aDraught);
      Draught(const Engine::Coord &aCoord, const Engine::Color &aColor, bool aIsKing = false);

      Engine::Coord coord() const;
      Engine::Color color() const;

      void moveTo(const Engine::Coord &aCoord);

      bool isKing() const;
      void makeKing();

      bool operator==(const Engine::Draught &aDraught) const;
      bool operator!=(const Engine::Draught &aDraught) const;
      bool operator<(const Engine::Draught &aDraught) const;
      bool operator>(const Engine::Draught &aDraught) const;

    private:
      typedef Engine::BitFlag<unsigned char, 0x40> KingFlag;

    private:
      Engine::CoordBase & coordRef();
      Engine::ColorBase & colorRef();
      KingFlag & kingFlagRef();

      const Engine::CoordBase & coordConstRef() const;
      const Engine::ColorBase & colorConstRef() const;
      const KingFlag & kingFlagConstRef() const;

    private:
      union DraughtDataStorage
      {
        Engine::CoordBase m_coord;
        KingFlag m_king;
        Engine::ColorBase m_color;
      };

    private:
      DraughtDataStorage m_value;
    };
  };
};

#endif //H_DRAUGHT_H
