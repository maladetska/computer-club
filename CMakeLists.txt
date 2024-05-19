cmake_minimum_required(VERSION 3.24)
project(ComputerClub
        VERSION 1.0
        DESCRIPTION "Soft for computer club"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
