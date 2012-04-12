message(STATUS "\n")
message(STATUS "Checkers engine build starting up...")

add_definitions(-Wall -Werror -Wextra)

include_directories( ${CMAKE_BINARY_DIR} )
#include_directories("../../logger")

set(engine_SRCS
    CoordBase.cpp
    Coord.cpp
    Color.cpp
   )

add_library(engine SHARED ${engine_SRCS})
target_link_libraries(engine)
