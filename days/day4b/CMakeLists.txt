add_executable(day4b main.cpp)

include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries (day4b ${OPENSSL_LIBRARIES})

install(TARGETS day4b DESTINATION day4)