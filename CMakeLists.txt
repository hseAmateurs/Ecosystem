cmake_minimum_required(VERSION 3.26)
project(Ecosystem)

set(CMAKE_CXX_STANDARD 14)

# Файлы для работы с текстурой клетки
set(TEXTURES
        src/textures/primaryCell.h
        src/textures/primaryCell.cpp
        src/textures/neutrophil.cpp
        src/textures/neutrophil.h
        src/textures/macrophage.cpp
        src/textures/macrophage.h
        src/textures/antibody.cpp
        src/textures/antibody.h
        src/textures/pathogen.cpp
        src/textures/pathogen.h
        src/textures/cellTextures.h
)

set(OBJECTS
        src/objects/cell.h
        src/objects/cell.cpp
        src/objects/pathogenCell.cpp
        src/objects/pathogenCell.h
        src/objects/bodyCell.cpp
        src/objects/bodyCell.h
        src/objects/macroCell.cpp
        src/objects/macroCell.h
        src/objects/neutroCell.cpp
        src/objects/neutroCell.h
        src/objects/hunterCell.cpp
        src/objects/hunterCell.h
)

set(UTILS
        src/utils/initialization.h
        src/utils/initialization.cpp
        src/utils/utils.h
)

# Исходные файлы
set(SOURCE_FILES
        src/main.cpp
)

# Название исполняемого файла
add_executable(Ecosystem
        ${SOURCE_FILES}
        ${TEXTURES}
        ${UTILS}
        ${OBJECTS}
)

# Для платформы windows используем статическую библиотеку sfml
if (WIN32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/sfml)
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()

# Поиск компонентов библиотеки
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    # Добавление headers
    target_include_directories(Ecosystem PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    target_link_libraries(Ecosystem PRIVATE m sfml-graphics sfml-window sfml-system)
endif ()
