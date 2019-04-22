project( SapphireEd )

file( GLOB EDITOR_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.cpp )

add_executable( sapphire_ed ${EDITOR_SOURCE_FILES} )

if( UNIX )
    cotire( sapphire_ed )
endif()