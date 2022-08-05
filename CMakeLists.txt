set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.8.5)

project(liboscparse)

set(TARGET_C_SOURCES  
    "message.c"
    "method.c"
    "pattern_match.c"
    "server.c"
    "timetag.c"
    "blob.c"
)

set(TARGET_C_INCLUDES
    "${CMAKE_SOURCE_DIR}/liboscparse"
    "${CMAKE_SOURCE_DIR}/liboscparse/lop"
)

add_compile_definitions(${TARGET_C_DEFINES})
include_directories(${TARGET_C_INCLUDES})

add_library(liboscparse STATIC
    "message.c"
    "method.c"
    "pattern_match.c"
    "server.c"
    "timetag.c"
    "blob.c"
)

target_include_directories(liboscparse
    PUBLIC
    "${CMAKE_SOURCE_DIR}/liboscparse"
    "${CMAKE_SOURCE_DIR}/liboscparse/lop"
)

target_link_libraries(liboscparse)