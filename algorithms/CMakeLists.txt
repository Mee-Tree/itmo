cmake_minimum_required(VERSION 3.15)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DLOCAL)

set(DIRS
    sort-heap-binary-search
    stack-queue-dsu
    dynamic-programming
    segment-tree
    search-tree
    tree-requests
    dfs-mst
    shortest-path-games
    strings)

foreach(DIR ${DIRS})
    file(GLOB FILES "${DIR}/*.cpp")
    foreach(FILE ${FILES})
        get_filename_component(NAME ${FILE} NAME_WLE)
        add_executable(${DIR}-${NAME} ${FILE})
    endforeach()
endforeach()