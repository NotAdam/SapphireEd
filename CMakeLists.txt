project( SapphireEd )
cmake_minimum_required( VERSION 3.10.2 )

set( CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake )

include( "cmake/paths.cmake" )
include( "cmake/compiler.cmake" )
include( "cmake/cotire.cmake" )

find_package( Vulkan REQUIRED )

set( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2/include )
set( SDL2_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2/lib/x64 )

find_file( SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2 )
find_library( SDL2_LIBRARY NAME SDL2 )

link_directories( ${SDL2_LIBRARY} )

include_directories( "deps" )

# sapphire deps
add_subdirectory( "deps/sapphire/deps/zlib" )
add_subdirectory( "deps/sapphire/deps/datReader" )

# deps
add_subdirectory( "deps/spdlog" )

#
add_subdirectory( "src/editor" )

