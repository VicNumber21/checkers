message(STATUS "\n")
message(STATUS "Checkers logger build starting up...")

add_definitions(-Wall -Werror -Wextra)

include_directories( ${CMAKE_BINARY_DIR} )

set(logger_SRCS
    LoggerManager.cpp
   )

add_library(logger SHARED ${logger_SRCS})
target_link_libraries(logger)
