cmake_minimum_required ( VERSION 3.26 )

get_latest_clang_format()
glob_sources_and_headers ( SOURCES HEADERS )

add_library ( cppdic INTERFACE
	${SOURCES} ${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_include_directories ( cppdic
	INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
