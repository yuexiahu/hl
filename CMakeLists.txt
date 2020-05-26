cmake_minimum_required(VERSION 3.1)
#================================
# project
#================================
project(hl VERSION 1.0.0 LANGUAGES C)

#================================
# include scripts
#================================
include(CTest)
include(CMakePackageConfigHelpers)

#================================
# options
#================================
option(HL_BUILD_SHARED_LIBS "Build shared library" OFF)

#================================
# build target
#================================
set(SOURCE_FILES
    src/hl_string.c
    src/hl_vector.c
    src/hl_list.c
    )

set(HEADER_FILES
    include/hl_defs.h
    include/hl_string.h
    include/hl_vector.h
    include/hl_list.h
    )

if(${HL_BUILD_SHARED_LIBS} STREQUAL "ON")
    add_library(hl SHARED ${SOURCE_FILES} ${HEADER_FILES})
    set_target_properties(hl PROPERTIES
        POSITION_INDEPENDENT_CODE 1)
else()
    add_library(hl STATIC ${SOURCE_FILES} ${HEADER_FILES})
endif()

add_library(hl::hl ALIAS hl)

target_include_directories(hl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/hl>
    )
set_target_properties(hl PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
target_compile_options(hl PUBLIC -fno-strict-aliasing)

#================================
# install target
#================================
install(TARGETS hl
    EXPORT hlTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/hl
    ARCHIVE DESTINATION lib/hl
    PUBLIC_HEADER DESTINATION include/hl
    )

#================================
# install cmake config
#================================
# generate version config file
write_basic_package_version_file(
    hlConfigVersion.cmake
    VERSION ${PROJECT_VERSION_MAJOR}
    COMPATIBILITY AnyNewerVersion
    )
# export target to config file
install(EXPORT hlTargets
    FILE hlTargets.cmake
    NAMESPACE hl::
    DESTINATION lib/cmake/hl
    )
# generate cmake config file with dependence
configure_file(hlConfig.cmake.in hlConfig.cmake @ONLY)
# install cmake config files
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/hlConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/hlConfigVersion.cmake
    DESTINATION lib/cmake/hl
    )

#================================
# build test
#================================
if(${BUILD_TESTING} STREQUAL "ON")
    add_subdirectory(tests)
endif()
