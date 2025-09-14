cmake_minimum_required(VERSION 3.10)

# Download GoogleTest if not present
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests test_broadcast.cpp)
target_link_libraries(runTests gtest gtest_main pthread)

add_test(NAME BroadcastTest COMMAND runTests)
