cmake_minimum_required(VERSION 3.31)

find_package(SDL3 REQUIRED)

add_executable (TinyEngine "TinyEngine.cpp" "TinyEngine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TinyEngine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(TinyEngine PRIVATE SDL3::SDL3)
