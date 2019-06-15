cmake_minimum_required(VERSION 3.0)

add_library(LoggerLibrary STATIC "../library/logger.c")
include_directories("../include")

add_executable(main main.c)

target_link_libraries(main LoggerLibrary)

add_test(UNIT_TESTS main)
