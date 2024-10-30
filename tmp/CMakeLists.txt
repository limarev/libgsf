cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

project(libgsf-tools
        DESCRIPTION "libgsf"
        LANGUAGES C)
# TODO remove this project

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_executable(test)

target_sources(test
               PRIVATE
               gsf.c)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})

find_package(gsf REQUIRED)

target_link_libraries(test PRIVATE gsf::gsf)
