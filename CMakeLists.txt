cmake_minimum_required(VERSION 3.6)

project(eventLoop)

set(EVENT_LOOP_SRCS
${CMAKE_CURRENT_LIST_DIR}/eventLoop.c
${CMAKE_CURRENT_LIST_DIR}/fifo.c
)

add_library(${CMAKE_PROJECT_NAME} ${EVENT_LOOP_SRCS})

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/generic-linked-list/src
    ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(generic-linked-list)
add_subdirectory(examples)
