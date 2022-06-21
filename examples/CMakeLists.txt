set(EXAMPLE_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

add_executable(eventLoop_example ${EXAMPLE_SRCS})

set_target_properties(eventLoop_example PROPERTIES EXCLUDE_FROM_ALL True)

target_link_libraries(eventLoop_example eventLoop gll)