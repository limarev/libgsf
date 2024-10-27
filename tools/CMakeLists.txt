cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

project(libgsf-tools
        DESCRIPTION "libgsf"
        LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_executable(gsf)

target_sources(gsf
               PRIVATE
               gsf.c)

target_include_directories(gsf PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(gsf PRIVATE libgsf)
