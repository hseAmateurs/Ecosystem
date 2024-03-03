//
// Created by Shon on 21.02.2024.
//

#ifndef ECOSYSTEM_UTILS_H
#define ECOSYSTEM_UTILS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../objects/pathogenCell.h"
#include "../objects/bodyCell.h"
#include "../objects/macroCell.h"
#include "../objects/neutroCell.h"

namespace utils {
    enum CellType {
        PATHOGEN,
        BODY,
        MACRO,
        NEUTRO
    };

    // Конфиг любой клетки
    typedef struct CellParam {
        CellParam() :
                radius(0), size(0), speed(0), amount(0), color(sf::Color::Black) { };

        float radius;
        int size;
        float speed;
        int amount;
        sf::Color color;
    } CellParam;

    // Конфиги всех клеток
    typedef struct {
        sf::Font font;
        std::vector<PathogenCell> pathogens;
        std::vector<BodyCell> bodies;
        std::vector<MacroCell> macroes;
        std::vector<NeutroCell> neutroes;
    } Field;
}

#endif //ECOSYSTEM_UTILS_H
