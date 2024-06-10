cmake_minimum_required ( VERSION 3.26 )

get_latest_clang_format()
glob_sources_and_headers ( SOURCES HEADERS )

add_executable ( tests
	${SOURCES} ${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_link_libraries ( tests
	LINK_PRIVATE cppdic
)

target_include_directories ( tests
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
