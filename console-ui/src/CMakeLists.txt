message(STATUS "\n")
message(STATUS "Checkers console UI build starting up...")

add_definitions(-Wall -Werror -Wextra)

include_directories("../../engine/src")
include_directories( ${CMAKE_BINARY_DIR} )
#include_directories("../../logger")

set(console_ui_SRCS
    BoardView.cpp
   )

add_library(console-ui SHARED ${console_ui_SRCS})
target_link_libraries(console-ui engine)
