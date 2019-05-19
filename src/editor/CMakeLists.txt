project( SapphireEd )

file( GLOB EDITOR_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.cpp
        imgui/*.cpp
        Rendering/Ext/*.cpp
        Component/*.cpp
        Component/Debug/*.cpp
        Component/Tools/*.cpp
        Util/*.cpp)

add_executable( sapphire_ed ${EDITOR_SOURCE_FILES} )

target_include_directories( sapphire_ed PUBLIC ${SDL2_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR} )
target_include_directories( sapphire_ed PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries( sapphire_ed SDL2 SDL2main ${Vulkan_LIBRARY} xivdat )

if( UNIX )
    cotire( sapphire_ed )
endif()

file( MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/fonts )

add_custom_command(
        TARGET sapphire_ed POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${EXECUTABLE_OUTPUT_PATH}/data )