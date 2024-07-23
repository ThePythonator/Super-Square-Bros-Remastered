cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Uncomment these to put the dlls in the same directory as the executable (useful if you don't have SDL2 installed and you're building from source)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Uncomment if you need to do some debugging :)
# set(CMAKE_FIND_DEBUG_MODE TRUE)

# Uncomment if no console should be created
# set(WINDOWS_NO_CONSOLE)

# Change your project name here
set(PROJECT_NAME Super_Square_Bros_Remastered)

project(${PROJECT_NAME})

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(GAME_SOURCES
	"Application.cpp"
	"Game.cpp"

	"MenuStages.cpp"
	"GameStages.cpp"

	"Physics.cpp"

	"PhysicsHandler.cpp"

	"Level.cpp"

	"Animation.cpp"
	
	"Entity.cpp"
	"PhysicsEntity.cpp"

	"Player.cpp"
)

set(FRAMEWORK_SOURCES
	"BaseGame.cpp"
	
	"BaseStage.cpp"
	"BaseTransition.cpp"

	"FadeTransition.cpp"
	
	"Input.cpp"
	"Keys.cpp"
	"Mouse.cpp"

	"Button.cpp"
	
	"Audio.cpp"
	
	"Graphics.cpp"
	"Window.cpp"

	"Font.cpp"
	"Image.cpp"
	"Spritesheet.cpp"

	"Colour.cpp"

	"Maths.cpp"
	"Transform.cpp"

	"Timer.cpp"
	"Curves.cpp"

	"File.cpp"
	"URL.cpp"

	"SDLUtils.cpp"
)

list(TRANSFORM GAME_SOURCES PREPEND src/game/)
list(TRANSFORM FRAMEWORK_SOURCES PREPEND src/framework/)

set(PROJECT_SOURCES ${FRAMEWORK_SOURCES};${GAME_SOURCES})

# Add any other files you want in the release here
set(PROJECT_DISTRIBS LICENSE README.md)
set(PROJECT_ASSETS assets)

if(APPLE)
    # Need to put the asssets inside the bundle (this is where SDL_GetBasePath points to)
    set(ASSETS_DEST bin/$<TARGET_FILE_NAME:${PROJECT_NAME}>.app/Contents/Resources)
else()
    set(ASSETS_DEST .)
endif()

set(CONSOLE_FLAG)
if (WINDOWS_NO_CONSOLE)
	set(CONSOLE_FLAG WIN32)
endif()

add_executable(${PROJECT_NAME} ${CONSOLE_FLAG} MACOSX_BUNDLE ${PROJECT_SOURCES})

include(fetch/get_json.cmake)
include(fetch/get_sdl2.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include/framework)
include_directories(${PROJECT_SOURCE_DIR}/include/game)
include_directories(${PROJECT_SOURCE_DIR}/include/external)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Link
target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2 SDL2::image SDL2::mixer nlohmann_json::nlohmann_json)


# Setup release packages
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	BUNDLE DESTINATION bin
)

install(FILES ${PROJECT_DISTRIBS}
	DESTINATION .
)

install(DIRECTORY ${PROJECT_ASSETS}
    DESTINATION ${ASSETS_DEST}
    FILES_MATCHING
    PATTERN "*.png"
    PATTERN "*.json"
)

if (UNIX AND NOT APPLE)
	# Todo: auto-gen this file using current PROJECT_NAME
    install(FILES extras/Launcher_Linux.sh
	    DESTINATION .
    )
endif()

if (NOT EMSCRIPTEN)
    # Install dependencies
    set(DEP_SEARCH_DIRS)
    # We built these, so we're installing them
    if(TARGET SDL2)
        list(APPEND DEP_SEARCH_DIRS $<TARGET_FILE_DIR:SDL2>)
    endif()

    if(TARGET SDL2_image)
        list(APPEND DEP_SEARCH_DIRS $<TARGET_FILE_DIR:SDL2_image>)# $<TARGET_FILE_DIR:png> $<TARGET_FILE_DIR:zlib>)
    endif()

    set(EXE_SUFFIX)
    if(APPLE)
        set(EXE_SUFFIX ".app")
    endif()

    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"\${CMAKE_INSTALL_PREFIX}/bin/$<TARGET_FILE_NAME:${PROJECT_NAME}>${EXE_SUFFIX}\" \"\" \"${DEP_SEARCH_DIRS}\")
    ")

endif()

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
