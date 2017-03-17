cmake_minimum_required(VERSION 3.6)
project(pa4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        FindPath.c
        Graph.c
        Graph.h
        Graphtest.c
        List.c
        List.h
        Makefile
        README)

add_executable(pa4 ${SOURCE_FILES})