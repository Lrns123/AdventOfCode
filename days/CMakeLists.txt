macro(install_day day)
	install(TARGETS day${day} DESTINATION day${day})
	install(FILES input DESTINATION day${day})
endmacro()

foreach(day RANGE 1 21)
	add_subdirectory(day${day})
endforeach(day)