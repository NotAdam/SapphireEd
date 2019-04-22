project( SapphireEd )
cmake_minimum_required( VERSION 3.0.2 )

set( CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake )

######################################
# Dependencies and compiler settings #
######################################
include( "cmake/paths.cmake" )
include( "cmake/compiler.cmake" )
include( "cmake/cotire.cmake" )


#
add_subdirectory( "src/editor" )