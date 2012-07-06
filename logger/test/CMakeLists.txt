message(STATUS "\n")
message(STATUS "Checkers logger TEST'S build starting up...")

add_definitions(-Wall -Werror -Wextra)

find_library(cppunit_found cppunit)
if(NOT cppunit_found)
    message(STATUS "cppunit lib is not found")
    message(STATUS "building of unit test is skipped")
    return()
endif(NOT cppunit_found)

include_directories("../src")
include_directories( ${CMAKE_BINARY_DIR} )

set(test_logger_SRCS
    main.cpp
   )

add_executable(test-logger ${test_logger_SRCS})

target_link_libraries(test-logger cppunit logger)

# TODO
# think about how to choose tests to be executed
# good tips can be found here
# http://www.cmake.org/pipermail/cmake/2007-March/013380.html
# http://www.cmake.org/pipermail/cmake/2007-March/013361.html
add_test(logger test-logger -v)
