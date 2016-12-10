#modules directories
set(FRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/framework)
set(COMMOM_DIR ${FRAMEWORK_DIR}/commom)
set(GRAPHICS_DIR ${FRAMEWORK_DIR}/graphics)
set(SDL_DIR ${FRAMEWORK_DIR}/sdl)
set(UI_DIR ${FRAMEWORK_DIR}/ui)
set(UTILS_DIR ${FRAMEWORK_DIR}/utils)

#
include_directories(${FRAMEWORK_DIR})

set(CPP_HEADER_FILES "\\/([a-z]|[A-Z]|[0-9]|_)+\\.(hpp|h)")
set(CPP_SOURCE_FILES "\\/([a-z]|[A-Z]|[0-9]|_)+\\.(cpp|c)")

source_group("Header Files\\framework\\commom" REGULAR_EXPRESSION "${COMMOM_DIR}${CPP_HEADER_FILES}")
source_group("Source Files\\framework\\commom" REGULAR_EXPRESSION "${COMMOM_DIR}${CPP_SOURCE_FILES}")

source_group("Header Files\\framework\\graphics" REGULAR_EXPRESSION "${GRAPHICS_DIR}${CPP_HEADER_FILES}")
source_group("Source Files\\framework\\graphics" REGULAR_EXPRESSION "${GRAPHICS_DIR}${CPP_SOURCE_FILES}")

source_group("Header Files\\framework\\sdl" REGULAR_EXPRESSION "${SDL_DIR}${CPP_HEADER_FILES}")
source_group("Source Files\\framework\\sdl" REGULAR_EXPRESSION "${SDL_DIR}${CPP_SOURCE_FILES}")

source_group("Header Files\\framework\\ui" REGULAR_EXPRESSION "${UI_DIR}${CPP_HEADER_FILES}")
source_group("Source Files\\framework\\ui" REGULAR_EXPRESSION "${UI_DIR}${CPP_SOURCE_FILES}")

source_group("Header Files\\framework\\utils" REGULAR_EXPRESSION "${UTILS_DIR}${CPP_HEADER_FILES}")
source_group("Source Files\\framework\\utils" REGULAR_EXPRESSION "${UTILS_DIR}${CPP_SOURCE_FILES}")

add_library(SDLApplication
        #framework
            #commom
                ${COMMOM_DIR}/resource_manager.hpp
            #graphics
                ${GRAPHICS_DIR}/buffer_object.hpp
                ${GRAPHICS_DIR}/buffer_object.cpp
                ${GRAPHICS_DIR}/definitions.hpp
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
                ${SDL_DIR}/definitions.hpp
                ${SDL_DIR}/sdl_app.hpp
                ${SDL_DIR}/sdl_app.cpp
                ${SDL_DIR}/sdl_error.hpp
                ${SDL_DIR}/sdl_message_box.hpp
                ${SDL_DIR}/sdl_message_box.cpp
                ${SDL_DIR}/sdl_window.hpp
                ${SDL_DIR}/sdl_window.cpp
            #ui
                ${UI_DIR}/box.hpp
                ${UI_DIR}/definitions.hpp
                ${UI_DIR}/drawer.hpp
                ${UI_DIR}/events.hpp
                ${UI_DIR}/widget.hpp
                ${UI_DIR}/widget.cpp
            #utils
                ${UTILS_DIR}/color.hpp
                ${UTILS_DIR}/fps_counter.hpp
                ${UTILS_DIR}/matrix.hpp
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