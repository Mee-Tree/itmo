cmake_minimum_required(VERSION 3.15)
project(graphs)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DLOCAL)

file(GLOB FILES "src/*.cpp")
foreach(file ${FILES})
    get_filename_component(name ${file} NAME_WLE)
    add_executable(${name} ${file})
endforeach()