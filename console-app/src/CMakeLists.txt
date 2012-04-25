message(STATUS "\n")
message(STATUS "Checkers app build starting up...")

add_definitions(-Wall -Werror -Wextra)

include_directories("../../engine/src")
include_directories("../../console-ui/src")
include_directories( ${CMAKE_BINARY_DIR} )

set(console_app_SRCS
    main.cpp
   )

add_executable(console-checkers ${console_app_SRCS})

target_link_libraries(console-checkers console-ui engine)
