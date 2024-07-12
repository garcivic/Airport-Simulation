cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

project(airport)

include_directories("includes")

# link main exec with header files && any of their definitions
# name this link SOURCES
set(SOURCES main.cpp includes/linked_list_functions/linkedlistfunctionsTemplated.h includes/node/node.h includes/queue/MyQueue.h includes/stack/MyStack.h)

add_executable(airport ${SOURCES})