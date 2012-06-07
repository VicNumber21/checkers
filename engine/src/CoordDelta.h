#ifndef H_COORD_DELTA_H
#define H_COORD_DELTA_H

#include "Coord.h"


namespace Checkers
{
  namespace Engine
  {
    class CoordDelta
    {
    public:
      enum DirectionFlag
      {
        ENorthFlag = 0x01
      , EEastFlag = 0x02
      , ESouthFlag = 0x04
      , EWestFlag = 0x08
      };

      enum Direction
      {
        ENorth = ENorthFlag
      , ENorthEast = ENorthFlag | EEastFlag
      , EEast = EEastFlag
      , ESouthEast = ESouthFlag | EEastFlag
      , ESouth = ESouthFlag
      , ESouthWest = ESouthFlag | EWestFlag
      , EWest = EWestFlag
      , ENorthWest = ENorthFlag | EWestFlag
      };

    public:
      CoordDelta(Direction aDirection, int aDistance);
      CoordDelta(int aDeltaX, int aDeltaY);
      CoordDelta(const CoordDelta &aDelta);

      int x() const;
      int y() const;

      bool isNull() const;
      bool isHorizontal() const;
      bool isVertical() const;
      bool isDiagonal() const;
      bool isSymmetric() const;

      Direction direction() const;
      bool isNorth() const;
      bool isSouth() const;
      bool isWest() const;
      bool isEast() const;

      int distance() const;

      CoordDelta & operator=(const CoordDelta &aDelta);
      bool operator==(const CoordDelta &aDelta) const;

    private:
      int m_dx;
      int m_dy;
    };

    Coord operator+(const Coord &aCoord, const CoordDelta &aDelta);
    Coord operator-(const Coord &aCoord, const CoordDelta &aDelta);

    CoordDelta operator-(const Coord &aFirst, const Coord &aSecond);
  };
};

#endif //H_COORD_DELTA_H
