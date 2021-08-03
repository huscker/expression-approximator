cmake_minimum_required(VERSION 3.10)

# set the project name
project(APPROXY LANGUAGES CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_compile_options(
    #-Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)


# add the executable
add_subdirectory(src)
add_executable(APPROXY main.cpp)
target_link_libraries(APPROXY GA_LIB)
target_link_libraries(APPROXY EXPR_LIB)