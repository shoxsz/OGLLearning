cmake_minimum_required(VERSION 3.7)
project(INTRO_CONCEPTS)
set(CMAKE_BUILD_TYPE release)

include_directories(${FRAMEWORK_DIR})

add_executable(
    intro_concepts
    main.cpp
    application.hpp
    application.cpp
    )

target_link_libraries(
    intro_concepts
    SDLApplication
)