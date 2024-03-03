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
#include "../objects/bCell.h"
#include "../objects/plasmaCell.h"

namespace utils {
    enum CellType {
        PATHOGEN,
        BODY,
        MACRO,
        NEUTRO,
        BCELL,
        PLASMA,
        COUNT
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
    struct Field {
        sf::Font font;
        std::vector<PathogenCell> pathogens;
        std::vector<BodyCell> bodies;
        std::vector<MacroCell> macroes;
        std::vector<NeutroCell> neutroes;
        std::vector<BCell> bCells;
        std::vector<PlasmaCell> plasmas;
    };
}

#endif //ECOSYSTEM_UTILS_H
