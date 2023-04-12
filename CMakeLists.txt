cmake_minimum_required(VERSION 3.20)
project(
    chip8emulator
    VERSION 0.1.0
    DESCRIPTION "Chip8 emulator"
    HOMEPAGE_URL "TODO"
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/project.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/project.h
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC cxx_std_20
)
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE -W -Wall -Wextra -pedantic -fPIC
)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/precompiled.hpp)

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src/)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)

FetchContent_MakeAvailable(
    argparse
    fmt
)
target_link_libraries(
    ${PROJECT_NAME}
    argparse
    fmt
)
