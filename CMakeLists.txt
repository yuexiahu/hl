cmake_minimum_required(VERSION 3.1)

project(hl)
include(CTest)

option(HL_BUILD_STATIC_LIBS "Build static library" ON)
option(HL_BUILD_SHARED_LIBS "Build shared library" OFF)

set(SOURCE_FILES
    src/hl_string.c
    src/hl_vector.c
    )

set(HEADER_FILES
    include/hl_defs.h
    include/hl_string.h
    include/hl_vector.h
    )

if(${HL_BUILD_SHARED_LIBS} STREQUAL "ON")
    add_library(hl_shared SHARED ${SOURCE_FILES} ${HEADER_FILES})
    add_library(hl::hl_shared ALIAS hl_shared)
    add_library(hl::hl ALIAS hl_shared)

    target_include_directories(hl_shared PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/hl>
        )

    target_compile_options(hl_shared PUBLIC
        -fno-strict-aliasing
        )
endif()

if(${HL_BUILD_STATIC_LIBS} STREQUAL "ON")
    add_library(hl STATIC ${SOURCE_FILES} ${HEADER_FILES})
    add_library(hl::hl_static ALIAS hl)
    if(NOT TARGET hl::hl)
        add_library(hl::hl ALIAS hl)
    endif()

    target_include_directories(hl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/hl>
        )

    target_compile_options(hl PUBLIC
        -fno-strict-aliasing
        )
endif()


if(${BUILD_TESTING} STREQUAL "ON")
    add_subdirectory(tests)
endif()
