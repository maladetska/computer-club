include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        computer_club_tests
        computer_club_test.cpp
)

target_link_libraries(
        computer_club_tests
        ComputerClubLib
        GTest::gtest_main
)

target_include_directories(computer_club_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(computer_club_tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static/input0.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static/input1.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)



