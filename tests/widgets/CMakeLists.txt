cmake_minimum_required(VERSION 3.5)
project(WIDGET_TEST)
set(CMAKE_BUILD_TYPE release)

set(DEPS_DIRECTORY C:/Users/PauloMarcio/Documents/development/libraries)

#includes
include_directories(
    ${DEPS_DIRECTORY}/SDL2.0.5/include
    ${DEPS_DIRECTORY}/glew-2.0.0/include
    ${CMAKE_SOURCE_DIR}/../../src/framework)

#link dependencies
link_directories(
    ${DEPS_DIRECTORY}/SDL2.0.5/lib
    ${DEPS_DIRECTORY}/glew-2.0.0/lib/)

add_executable(
    WidgetTest 
    main.cpp 
    sdl_box.hpp 
    sdl_box.cpp
    ${CMAKE_SOURCE_DIR}/../../src/framework/ui/widget.cpp
    )

target_link_libraries(
    WidgetTest 

    glew32
    SDL2
    SDL2main
    SDL2_Image
    Opengl32)
