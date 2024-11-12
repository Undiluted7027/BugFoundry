cmake_minimum_required(VERSION 3.10)

project(bugfoundry VERSION 1.0 DESCRIPTION "BugFoundry" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(main)
include_directories(src)
include_directories(include)
include_directories(test)

file(GLOB MAIN "main/Main.cpp")
file(GLOB SOURCES_CXX "src/*.cpp")
file(GLOB SOURCES_H "include/*.hpp")
file(GLOB TEST "test/test.cpp")

add_executable(system ${MAIN} ${SOURCES_CXX} ${SOURCES_H})
add_executable(test ${TEST} ${SOURCES_CXX} ${SOURCES_H})
