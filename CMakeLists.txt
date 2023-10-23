cmake_minimum_required(VERSION 3.18)

project(pikiwidb-folly
        DESCRIPTION "Part of folly library which pikiwidb depends on"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE FOLLY_SRC ${PROJECT_SOURCE_DIR}/folly/*.cpp)
add_compile_definitions(FOLLY_NO_CONFIG)

add_library(pikiwidb-folly ${FOLLY_SRC})
target_include_directories(pikiwidb-folly PUBLIC $<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}>)
