cmake_minimum_required(VERSION 3.2.0)
project(AdventOfCode)

set (CMAKE_CXX_STANDARD 14)

find_package(OpenSSL)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
endif()

add_subdirectory(days)