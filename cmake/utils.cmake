function ( fetch_clang_format )
	file (
		DOWNLOAD
			"https://raw.githubusercontent.com/nerudaj/clang-format/main/.clang-format"
			"${CMAKE_BINARY_DIR}/.clang-format"
	)
endfunction()

function ( get_latest_clang_format )
	file (
		COPY "${CMAKE_BINARY_DIR}/.clang-format"
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}" )
endfunction()

function ( glob_sources_and_headers src_outvarname hdr_outvarname )
    file ( GLOB_RECURSE LOCAL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include**/*.hpp" )
	file ( GLOB_RECURSE LOCAL_SOURCES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src**/*.cpp" )
	source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LOCAL_HEADERS})
	source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LOCAL_SOURCES_CPP})
	set ( ${hdr_outvarname} "${LOCAL_HEADERS}" PARENT_SCOPE )
	set ( ${src_outvarname} "${LOCAL_SOURCES_CPP}" PARENT_SCOPE )
endfunction ()