cmake_minimum_required(VERSION 3.7)
project(OGLLearning)
set(CMAKE_BUILD_TYPE release)

#this is the default output directory to use in all cmake lists
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../out)

#libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
#executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/exes)

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

#build the framework
include(framework/CMakeLists.txt)

#build the projects
include(projects/CMakeLists.txt)