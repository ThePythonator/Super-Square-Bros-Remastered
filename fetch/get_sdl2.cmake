# defines SDL2::SDL2, SDL2::SDL2main and SDL2::image targets

if(EMSCRIPTEN)
    # Emscripten-specific magic
    add_library(SDL2::SDL2 INTERFACE IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        INTERFACE_COMPILE_OPTIONS "SHELL:-s USE_SDL=2"
        INTERFACE_LINK_LIBRARIES "-s USE_SDL=2"
    )

    add_library(SDL2::SDL2main INTERFACE IMPORTED)

    add_library(SDL2::image INTERFACE IMPORTED)
    set_target_properties(SDL2_image::SDL2_image PROPERTIES
        INTERFACE_COMPILE_OPTIONS "SHELL:-s USE_SDL_IMAGE=2"
        INTERFACE_LINK_LIBRARIES "-s USE_SDL_IMAGE=2"
    )
else()
    # Check for system SDL2
    # Currently breaks for me
    find_package(SDL2 QUIET NO_SYSTEM_ENVIRONMENT_PATH)
    find_package(SDL2_image QUIET) # will probably fail
endif()

# Didn't find it, build from source
include(FetchContent)

if(NOT TARGET SDL2::SDL2)
    message("Did not find SDL2, building from source.")

    FetchContent_Populate(SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG        release-2.30.5
    )
    add_subdirectory(${sdl2_SOURCE_DIR} SDL2 EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET SDL2::image)
    # get SDL2_image (no released version has CMake support)
    FetchContent_Populate(SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG        release-2.8.2
    )
    add_subdirectory(${sdl2_image_SOURCE_DIR} SDL2_image EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET SDL2::mixer)
    set(SDL2MIXER_OPUS OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_MOD OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_MIDI OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_WAVPACK OFF CACHE BOOL "" FORCE)

    FetchContent_Populate(SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
        GIT_TAG        release-2.8.0
    )
    add_subdirectory(${sdl2_mixer_SOURCE_DIR} SDL2_mixer EXCLUDE_FROM_ALL)
endif()