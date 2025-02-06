cmake_minimum_required(VERSION 3.28)
project(graphs C)

set(CMAKE_C_STANDARD 11)

add_library(graphs
        src/graph_am.c
        include/graph.h
        src/graph_ll.c
        src/graph_common.c
)

target_include_directories(graphs PUBLIC include)

add_executable(tests tests/tests.c)
target_link_libraries(tests PRIVATE graphs)

install(TARGETS graphs DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

