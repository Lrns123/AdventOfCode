add_executable(day7 day7.cpp logicgates.hpp logicgates.cpp logicnetwork.hpp logicnetwork.cpp)

install(TARGETS day7 DESTINATION day7)
install(FILES input DESTINATION day7)