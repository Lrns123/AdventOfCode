if (${OPENSSL_FOUND})
	add_executable(day4 day4.cpp md5.cpp md5.hpp)

	include_directories(${OPENSSL_INCLUDE_DIR})
	target_link_libraries (day4 ${OPENSSL_LIBRARIES})

	install(TARGETS day4 DESTINATION day4)
	install(FILES input DESTINATION day4)
endif()