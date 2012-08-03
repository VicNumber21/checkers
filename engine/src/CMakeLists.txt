message(STATUS "\n")
message(STATUS "Checkers engine build starting up...")

add_definitions(-Wall -Werror -Wextra)

include_directories("../../logger/src")
include_directories( ${CMAKE_BINARY_DIR} )

set(engine_SRCS
    Error.cpp
    CoordBase.cpp
    Coord.cpp
    CoordDelta.cpp
    CoordSequence.cpp
    ColorBase.cpp
    Color.cpp
    Draught.cpp
    Board.cpp
    Maybe.cpp
    RulesOfGame.cpp
    RulesOfGameManager.cpp
    RulesOfGameInstances.cpp
    Move.cpp
    PositionAnalyser.cpp
    AmericanCheckersPositionAnalyser.cpp
    AmericanCheckersBoardTraits.cpp
    WalkerBase.cpp
    Iteration.cpp
    Player.cpp
    RandomChoiceMind.cpp
    JustOwnMoveAheadMind.cpp
    GameManager.cpp
   )

add_library(engine SHARED ${engine_SRCS})
target_link_libraries(engine logger)
