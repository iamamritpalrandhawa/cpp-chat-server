cmake_minimum_required(VERSION 3.10)
project(cpp_chat_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include tests directory
enable_testing()
add_subdirectory(tests)
