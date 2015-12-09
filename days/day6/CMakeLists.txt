add_executable(day6 day6.cpp instruction.hpp instruction.cpp)

include_directories(${Boost_INCLUDE_DIR})

install(TARGETS day6 DESTINATION day6)
install(FILES input DESTINATION day6)