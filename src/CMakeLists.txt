cmake_minimum_required(VERSION 3.7)
project(SDLApplication)
set(CMAKE_BUILD_TYPE release)

#this is the default output directory to use in all cmake lists
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../out)

set(LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)

#modules directories
set(FRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/framework)
set(GRAPHICS_DIR ${FRAMEWORK_DIR})
set(SDL_DIR ${FRAMEWORK_DIR}/sdl)
set(UI_DIR ${FRAMEWORK_DIR}/ui)
set(UTILS_DIR ${FRAMEWORK_DIR}/utils)

#
include_directories(${FRAMEWORK_DIR})

#dependencies directories(YOU(THE USER) PROBABLY NEED TO CHANGE IT!!)
set(DEPS_DIRECTORY C:/Users/PauloMarcio/Documents/development/libraries)

#includes
include_directories(
    ${DEPS_DIRECTORY}/SDL2.0.5/include)

#link dependencies
link_directories(
    ${DEPS_DIRECTORY}/SDL2.0.5/lib)

include_directories(
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/framework/graphics
    ${CMAKE_SOURCE_DIR}/sdl
    ${CMAKE_SOURCE_DIR}/ui)


add_library(SDLApplication
        #framework
            #graphics - not yet
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
                ${UTILS_DIR}/fps_counter.hpp
                ${UTILS_DIR}/scene.hpp
        )
    
#linking
target_link_libraries(
    SDLApplication 
    SDL2
    SDL2main
    Opengl32)

#build the projects
add_subdirectory(projects)