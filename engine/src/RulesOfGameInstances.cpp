#include "RulesOfGameInstances.h"
#include "AmericanCheckersBoardTraits.h"
#include "AmericanCheckersPositionAnalyser.h"

using namespace Checkers::Engine;


template <class BOARD_TRAITS, class POSITION_ANALYSER>
void RulesOfGameInstanceTemplate<BOARD_TRAITS, POSITION_ANALYSER>::activate()
{
  m_objects.reset(new RulesOfGameObjects);
}

template <class BOARD_TRAITS, class POSITION_ANALYSER>
void RulesOfGameInstanceTemplate<BOARD_TRAITS, POSITION_ANALYSER>::deactivate()
{
  m_objects.reset();
}

template <class BOARD_TRAITS, class POSITION_ANALYSER>
const BoardTraits & RulesOfGameInstanceTemplate<BOARD_TRAITS, POSITION_ANALYSER>::boardTraits() const
{
  throwIfNotActive();
  return m_objects->m_board_traits;
}

template <class BOARD_TRAITS, class POSITION_ANALYSER>
PositionAnalyser & RulesOfGameInstanceTemplate<BOARD_TRAITS, POSITION_ANALYSER>::positionAnalyser()
{
  throwIfNotActive();
  return m_objects->m_position_analyser;
}

template <class BOARD_TRAITS, class POSITION_ANALYSER>
void RulesOfGameInstanceTemplate<BOARD_TRAITS, POSITION_ANALYSER>::throwIfNotActive() const
{
  if(!m_objects)
    throw RulesOfGameInstanceError();
}

template class RulesOfGameInstanceTemplate<AmericanCheckersBoardTraits, AmericanCheckersPositionAnalyser>;
