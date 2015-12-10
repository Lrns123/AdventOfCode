cmake_minimum_required(VERSION 3.2.0)
project(AdventOfCode)

set (CMAKE_CXX_STANDARD 14)

find_package(OpenSSL REQUIRED)

add_subdirectory(days)