project(checkers)
cmake_minimum_required(VERSION 2.6)
message(STATUS "\n")
message(STATUS "checkers build starting up...")
message(STATUS "\n")
message(STATUS "========== Environment info ==========")
message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
if(MSVC)
message(STATUS "Compiler: MSVC, version: " ${MSVC_VERSION})
endif(MSVC)
if(BORLAND)
message(STATUS "Compiler: BCC")
endif(BORLAND)
else(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
message(STATUS "Compiler: GCC")
endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
message(STATUS "CMake generates " ${CMAKE_GENERATOR})
message(STATUS "======================================")

# TODO
# enable / disable testing
# basing on project configuration
enable_testing()

add_subdirectory(engine)
add_subdirectory(console-ui)
add_subdirectory(console-app)
