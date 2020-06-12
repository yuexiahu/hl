cmake_minimum_required(VERSION 3.1)

project(tests)

function(test_unit unit)
    set(test_unit ${unit})
    configure_file(test.c.in "${unit}_main.c")
    add_executable(${unit} "${unit}_main.c" ${ARGV})
    target_include_directories(${unit} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${unit} hl::hl)
    add_test(NAME ${unit} COMMAND ${unit})
endfunction()

test_unit(test_string test_string.c)
test_unit(test_vector test_vector.c)
test_unit(test_list test_list.c)
test_unit(test_slist test_slist.c)
test_unit(test_hashmap test_hashmap.c)

