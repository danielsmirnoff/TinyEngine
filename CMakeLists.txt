cmake_minimum_required(VERSION 3.22)
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
project(TinyEngine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_SUPPRESS_REGENERATION true) # disable ZERO_CHECK target creation

include_directories(include src)
link_directories(lib)

file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${SOURCES})
add_executable(TinyEngine ${SOURCES})

if (APPLE)
    target_link_libraries(TinyEngine libSDL3.dylib libSDL3_Mixer.dylib)
elseif (WIN32)
    target_link_libraries(TinyEngine SDL3.lib)
endif ()

add_custom_command(TARGET TinyEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:TinyEngine>/resources
)