cmake_minimum_required(VERSION 3.26)
project(Ecosystem)

set(CMAKE_CXX_STANDARD 14)

# Исходные файлы
set(SOURCE_FILES
        src/main.cpp
        src/textures/cell.h
        src/textures/cell.cpp
        src/textures/neutrophil.cpp
        src/textures/neutrophil.h
        src/textures/macrophage.cpp
        src/textures/macrophage.h
        src/textures/antibody.cpp
        src/textures/antibody.h
        src/textures/pathogen.cpp
        src/textures/pathogen.h
        src/textures/cellTextures.h)

# Название исполняемого файла
add_executable(Ecosystem ${SOURCE_FILES})

# Для платформы windows используем статическую библиотеку sfml
if(WIN32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/sfml)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

# Поиск компонентов библиотеки
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    # Добавление headers
    target_include_directories(Ecosystem PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    target_link_libraries(Ecosystem PRIVATE m sfml-graphics sfml-window sfml-system)
endif()
