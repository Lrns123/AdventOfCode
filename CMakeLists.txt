cmake_minimum_required(VERSION 3.2.0)
project(AdventOfCode)

find_package(OpenSSL REQUIRED)
find_package(Boost 1.59 REQUIRED)

add_subdirectory(days)