cmake_minimum_required(VERSION 3.26)
project(Ecosystem)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE
        src/main.cpp)

add_executable(Ecosystem ${SOURCE})

if(WIN32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/sfml)
endif()
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    target_include_directories(Ecosystem PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(Ecosystem PRIVATE m sfml-graphics sfml-window sfml-system)
endif()
