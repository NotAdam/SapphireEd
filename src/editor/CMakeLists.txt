project( SapphireEd )

file( GLOB EDITOR_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.cpp
        imgui/*.cpp
        Rendering/Ext/*.cpp
        Component/*.cpp
        Component/TestComponent/*.cpp )

add_executable( sapphire_ed ${EDITOR_SOURCE_FILES} )

target_include_directories( sapphire_ed PUBLIC ${SDL2_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR} )
target_include_directories( sapphire_ed PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries( sapphire_ed SDL2 SDL2main ${Vulkan_LIBRARY} )

if( UNIX )
    cotire( sapphire_ed )
endif()