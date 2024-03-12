cmake_minimum_required(VERSION 3.26)
project(Ecosystem)

set(CMAKE_CXX_STANDARD 14)

# Файлы для работы с текстурой клетки
set(TEXTURES
        src/textures/cellTexture.h
        src/textures/cellTexture.cpp
        src/textures/animPlasma.cpp
        src/textures/animations.h
        src/textures/animBody.cpp
        src/textures/animMacro.cpp
        src/textures/animPathogen.cpp
        src/textures/animAntibody.cpp
        src/textures/animNeutro.cpp
        src/textures/animBCell.cpp
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
        src/objects/plasmaCell.h
        src/objects/plasmaCell.cpp
        src/objects/bCell.h
        src/objects/bCell.cpp
        src/objects/Antibody.h
        src/objects/Antibody.cpp
)

set(UTILS
        src/utils/initialization.h
        src/utils/initialization.cpp
        src/utils/utils.h
        src/utils/cellTypes.h
        src/utils/settings.h
        src/utils/cells.h
        src/utils/freeMemory.h
        src/utils/brain.cpp
        src/utils/brain.h
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
