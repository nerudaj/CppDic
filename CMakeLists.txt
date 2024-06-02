cmake_minimum_required ( VERSION 3.26 )

project ( CppDic )

include ( "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpp.cmake" )
include ( "${CMAKE_CURRENT_SOURCE_DIR}/cmake/utils.cmake" )

fetch_clang_format()

add_subdirectory ( "${CMAKE_CURRENT_SOURCE_DIR}/lib" )
add_subdirectory ( "${CMAKE_CURRENT_SOURCE_DIR}/tests" )
