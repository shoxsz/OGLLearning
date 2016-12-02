cmake_minimum_required(VERSION 3.7)
project(SDLApplication)
set(CMAKE_BUILD_TYPE release)

#this is the default output directory to use in all cmake lists
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../out)

set(LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)

#modules directories
set(FRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/framework)
set(COMMOM_DIR ${FRAMEWORK_DIR}/commom)
set(GRAPHICS_DIR ${FRAMEWORK_DIR}/graphics)
set(SDL_DIR ${FRAMEWORK_DIR}/sdl)
set(UI_DIR ${FRAMEWORK_DIR}/ui)
set(UTILS_DIR ${FRAMEWORK_DIR}/utils)

#files
set(COMMOM_FILES)

#
include_directories(${FRAMEWORK_DIR})

#dependencies directories(YOU(THE USER) PROBABLY NEED TO CHANGE IT!!)
set(DEPS_DIRECTORY C:/Users/PauloMarcio/Documents/development/libraries)

#includes
include_directories(
    ${DEPS_DIRECTORY}/SDL2.0.5/include
    ${DEPS_DIRECTORY}/glew-2.0.0/include)

#link dependencies
link_directories(
    ${DEPS_DIRECTORY}/SDL2.0.5/lib
    ${DEPS_DIRECTORY}/glew-2.0.0/lib/)

include_directories(
    ${FRAMEWORK_DIR}/
    #${FRAMEWORK_DIR}/commom
    #${FRAMEWORK_DIR}/graphics
    #${FRAMEWORK_DIR}/sdl
    #${FRAMEWORK_DIR}/ui
    #${FRAMEWORK_DIR}/utils
    )

set(CPP_FILES_REGEX "\\b(\\w|\\d)+\\b\\.(hpp|cpp|c|h)")

#add folders in the visual studio projects
source_group("framework/commom" REGULAR_EXPRESSION "${COMMOM_DIR}\/${CPP_FILES_REGEX}")
source_group("framework/graphics" REGULAR_EXPRESSION "${GRAPHICS_DIR}\/${CPP_FILES_REGEX}")
source_group("framework/sdl" REGULAR_EXPRESSION "${SDL_DIR}\/${CPP_FILES_REGEX}")
source_group("framework/ui" REGULAR_EXPRESSION "${UI_DIR}\/${CPP_FILES_REGEX}")
source_group("framework/utils" REGULAR_EXPRESSION "${UTILS_DIR}\/${CPP_FILES_REGEX}")

add_library(SDLApplication
        #framework
            #commom
                ${COMMOM_DIR}/resource_manager.hpp
            #graphics
                ${GRAPHICS_DIR}/buffer_object.hpp
                ${GRAPHICS_DIR}/buffer_object.cpp
                ${GRAPHICS_DIR}/enums.hpp
                ${GRAPHICS_DIR}/shader.hpp
                ${GRAPHICS_DIR}/shader.cpp
                ${GRAPHICS_DIR}/shader_program.hpp
                ${GRAPHICS_DIR}/shader_program.cpp
                ${GRAPHICS_DIR}/sprite_batch.hpp
                ${GRAPHICS_DIR}/sprite_batch.cpp
                ${GRAPHICS_DIR}/texture.hpp
                ${GRAPHICS_DIR}/texture.cpp
                ${GRAPHICS_DIR}/texture_manager.hpp
                ${GRAPHICS_DIR}/texture_manager.cpp
                ${GRAPHICS_DIR}/vertices.hpp
            #sdl
                ${SDL_DIR}/sdl_app.hpp
                ${SDL_DIR}/sdl_app.cpp
                ${SDL_DIR}/sdl_error.hpp
                ${SDL_DIR}/sdl_message_box.hpp
                ${SDL_DIR}/sdl_message_box.cpp
                ${SDL_DIR}/sdl_window.hpp
                ${SDL_DIR}/sdl_window.cpp
            #ui
                ${UI_DIR}/box.hpp
                ${UI_DIR}/container.hpp
                ${UI_DIR}/container.cpp
                ${UI_DIR}/drawer.hpp
                ${UI_DIR}/position.hpp
                ${UI_DIR}/rectangle.hpp
                ${UI_DIR}/widget.hpp
                ${UI_DIR}/widget.cpp
            #utils
                ${UTILS_DIR}/color.hpp
                ${UTILS_DIR}/fps_counter.hpp
                ${UTILS_DIR}/point.hpp
                ${UTILS_DIR}/pointer_allocator.hpp
                ${UTILS_DIR}/rect.hpp
                ${UTILS_DIR}/scene.hpp
                ${UTILS_DIR}/size.hpp
        )
    
#linking
target_link_libraries(
    SDLApplication 

    glew
    SDL2
    SDL2main
    SDL2_Image
    Opengl32)

#build the projects
add_subdirectory(projects)