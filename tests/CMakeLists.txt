cmake_minimum_required(VERSION 3.1)

project(tests)

set(SOURCE_FILES
    test.c
    test_string.c
    test_vector.c
    test_list.c
    )

set(HEADER_FILES
    simpletest.h
    )

add_executable(tests ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(tests hl::hl)

add_test(NAME tests COMMAND tests)
