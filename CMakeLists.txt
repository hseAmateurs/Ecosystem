cmake_minimum_required(VERSION 3.26)
project(Ecosystem)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE
        src/main.cpp)

add_executable(Ecosystem ${SOURCE})

target_link_libraries(Ecosystem m)
