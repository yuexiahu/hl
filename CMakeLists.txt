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
# add sub directories
#================================
add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

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
