cmake_minimum_required(VERSION 3.0)

project(logger-c C)

add_library(Logger STATIC library/logger.c)

include_directories("./include")

set(SOURCE_FILES main.c)
add_executable(logger-c ${SOURCE_FILES})

target_link_libraries(logger-c Logger)

enable_testing()
add_subdirectory(tests)
