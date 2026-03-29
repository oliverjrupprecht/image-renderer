cmake_minimum_required(VERSION 3.16)
project(iv)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

add_executable(iv iv.c)

target_link_libraries(iv PRIVATE SDL2::SDL2)
target_include_directories(iv PRIVATE ${SDL2_INCLUDE_DIRS})
