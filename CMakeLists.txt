cmake_minimum_required(VERSION 3.29)
project(graphs C)

set(CMAKE_C_STANDARD 11)

add_executable(graphs src/main.c src/graph_am.c include/graph.h
        src/graph_ll.c
        src/graph_common.c)
