cmake_minimum_required(VERSION 3.6)
project(pa5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        FindComponents.c
        Graph.c
        Graph.h
        GraphClient.c
        GraphTest.c
        List.c
        List.h
        Makefile
        output
        README)

add_executable(pa5 ${SOURCE_FILES})