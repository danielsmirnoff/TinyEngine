cmake_minimum_required(VERSION 3.25)

# ===========================================================================
#  SETTINGS - change these
# ===========================================================================
set(PROJECT_NAME    "MyGame")                       # project name
set(EXE_NAME        "MyGame")                       # output file -> MyGame.exe
set(CPP_STANDARD    20)                             # 17, 20, 23

set(SRC_DIR         "${CMAKE_SOURCE_DIR}/src")      # every .cpp in here is compiled
set(EXTERNAL_DIR    "${CMAKE_SOURCE_DIR}/external") # git submodules live here
set(ASSETS_DIR      "${CMAKE_SOURCE_DIR}/assets")   # copied next to the exe
set(OUTPUT_DIR      "${CMAKE_BINARY_DIR}/bin")      # where the .exe ends up

set(SHOW_CONSOLE    ON)                             # OFF = no console window
set(STATIC_RUNTIME  ON)                             # ON = no libstdc++/libgcc DLLs needed
# ===========================================================================

# C is needed too: SDL3 and GLFW are C libraries
project(${PROJECT_NAME} LANGUAGES C CXX)

# Default to Debug when no build type is given (single-config generators like Ninja)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD ${CPP_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)               # build/compile_commands.json for IntelliSense/clangd
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# MSVC only: static CRT must be set before the deps are added so everything matches
if(MSVC AND STATIC_RUNTIME)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# ---------------------------------------------------------------------------
#  Make sure the submodules were actually cloned
# ---------------------------------------------------------------------------
function(require_submodule dir sentinel)
    if(NOT EXISTS "${EXTERNAL_DIR}/${dir}/${sentinel}")
        message(FATAL_ERROR
            "external/${dir} looks empty.\n"
            "Run:  git submodule update --init --recursive")
    endif()
endfunction()

require_submodule(SDL    CMakeLists.txt)
require_submodule(GLFW   CMakeLists.txt)
require_submodule(ENTT   CMakeLists.txt)
require_submodule(IMGUI  imgui.h)
require_submodule(SPDLOG CMakeLists.txt)

# ---------------------------------------------------------------------------
#  Dependencies
#  SYSTEM = their headers are treated as system headers, so -Wall/-Wextra
#  on your code won't spam warnings from inside the libraries.
# ---------------------------------------------------------------------------

# ---- SDL3 (built as a static lib -> no SDL3.dll to copy around) ----
set(SDL_SHARED       OFF CACHE BOOL "" FORCE)
set(SDL_STATIC       ON  CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS        OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES     OFF CACHE BOOL "" FORCE)
add_subdirectory(${EXTERNAL_DIR}/SDL SYSTEM)

# ---- GLFW ----
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
add_subdirectory(${EXTERNAL_DIR}/GLFW SYSTEM)

# ---- EnTT (header-only) ----
add_subdirectory(${EXTERNAL_DIR}/ENTT SYSTEM)

# ---- spdlog (compiled static lib, uses its bundled fmt) ----
add_subdirectory(${EXTERNAL_DIR}/SPDLOG SYSTEM)

# ---- Dear ImGui (has no CMakeLists, so we build it ourselves) ----
set(IMGUI_DIR ${EXTERNAL_DIR}/IMGUI)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    # Backends: SDL3 + SDL_Renderer, and GLFW + OpenGL3.
    # Delete the pair you don't use.
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui SYSTEM PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
target_link_libraries(imgui PUBLIC SDL3::SDL3-static glfw)
if(WIN32)
    target_link_libraries(imgui PUBLIC opengl32)
endif()

# ---------------------------------------------------------------------------
#  Your app
# ---------------------------------------------------------------------------

# Grab every .cpp file under SRC_DIR (re-scanned automatically when files are added/removed)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")

add_executable(${EXE_NAME} ${SOURCES})

target_include_directories(${EXE_NAME} PRIVATE ${SRC_DIR})

# Linking the targets also brings in their include paths and defines, so
# #include <SDL3/SDL.h>, <GLFW/glfw3.h>, <entt/entt.hpp>, <spdlog/spdlog.h>,
# "imgui.h" all just work.
target_link_libraries(${EXE_NAME} PRIVATE
    SDL3::SDL3-static
    glfw
    EnTT::EnTT
    imgui
    spdlog::spdlog
)

if(MSVC)
    target_compile_options(${EXE_NAME} PRIVATE /W4 /permissive- /utf-8)
else()
    target_compile_options(${EXE_NAME} PRIVATE -Wall -Wextra)
endif()

if(STATIC_RUNTIME AND MINGW)
    target_link_options(${EXE_NAME} PRIVATE
        -static-libgcc -static-libstdc++
        -Wl,-Bstatic -lwinpthread -Wl,-Bdynamic
    )
endif()

# Works for both gcc (-mwindows) and MSVC (/SUBSYSTEM:WINDOWS)
if(NOT SHOW_CONSOLE)
    set_target_properties(${EXE_NAME} PROPERTIES WIN32_EXECUTABLE ON)
endif()

# Copy assets next to the exe after each build
if(EXISTS ${ASSETS_DIR})
    add_custom_command(TARGET ${EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${OUTPUT_DIR}/assets"
    )
endif()