#================================
# build target
#================================
set(SOURCE_FILES
    hl_string.c
    hl_vector.c
    hl_list.c
    hl_slist.c
    hl_hashmap.c
    )

set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/hl_defs.h
    ${CMAKE_SOURCE_DIR}/include/hl_string.h
    ${CMAKE_SOURCE_DIR}/include/hl_vector.h
    ${CMAKE_SOURCE_DIR}/include/hl_list.h
    ${CMAKE_SOURCE_DIR}/include/hl_slist.h
    ${CMAKE_SOURCE_DIR}/include/hl_hashmap.h
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
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/hl>
    )
set_target_properties(hl PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
#target_compile_options(hl PUBLIC -fno-strict-aliasing)
