project( SapphireEd )
cmake_minimum_required( VERSION 3.10.2 )

set( CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake )

include( "cmake/paths.cmake" )
include( "cmake/compiler.cmake" )
include( "cmake/cotire.cmake" )

find_package( Vulkan REQUIRED )
message("Vulkan found? " ${VULKAN_FOUND})
message("Alright, where is it? " ${Vulkan_LIBRARY})
message("And I can include it? " ${Vulkan_INCLUDE_DIR})

set( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/external/SDL2/include )
set( SDL2_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/deps/external/SDL2/lib/x64 )

find_file( SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2 )
find_library( SDL2_LIBRARY NAME SDL2 )

link_directories(${SDL2_LIBRARY} )

include_directories( "deps" )

#
add_subdirectory( "src/editor" )