message(STATUS "\n")
message(STATUS "Checkers engine TEST'S build starting up...")

add_definitions(-Wall -Werror -Wextra)

find_library(cppunit_found cppunit)
if(NOT cppunit_found)
    message(STATUS "cppunit lib is not found")
    message(STATUS "building of unit test is skipped")
    return()
endif(NOT cppunit_found)

include_directories("../src")
include_directories("../../console-ui/src")
include_directories( ${CMAKE_BINARY_DIR} )

set(test_engine_SRCS
    main.cpp
    PrettyPrint.cpp
    CoordTests.cpp
    CoordSequenceTests.cpp
    ColorTests.cpp
    DraughtTests.cpp
    BoardTests.cpp
    MoveTests.cpp
   )

add_executable(test-engine ${test_engine_SRCS})

target_link_libraries(test-engine cppunit engine console-ui)

# TODO
# think about how to choose tests to be executed
# good tips can be found here
# http://www.cmake.org/pipermail/cmake/2007-March/013380.html
# http://www.cmake.org/pipermail/cmake/2007-March/013361.html
add_test(engine test-engine -v)
