#search all subdirectories, these must have a CMakeLists file to build the project
macro(SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
        list(APPEND dirlist ${child})
        endif()
    endforeach(child)
    set(${result} ${dirlist})
endmacro(SUBDIRLIST)

SUBDIRLIST(projects ${CMAKE_CURRENT_LIST_DIR})

#add all the projects
foreach(project ${projects})
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${project})
endforeach()