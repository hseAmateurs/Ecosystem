//
// Created by Shon on 21.02.2024.
//

#ifndef ECOSYSTEM_UTILS_H
#define ECOSYSTEM_UTILS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../textures/animations.h"
#include "../objects/temperature.h"
#include "../objects/gameMenu.h"

class BCell;

class BodyCell;

class PathogenCell;

class MacroCell;

class PlasmaCell;

class NeutroCell;

class Antibody;

class Temperature;

namespace utils {
    // Конфиг любой клетки
    struct CellParam {
        CellParam() :
                radius(0), size(0), speed(0), amount(0), color(sf::Color::Black), animation(texture::bodyCell) { };

        float radius;
        int size;
        float speed;
        int amount;
        sf::Color color;
        texture::AnimationParameters animation;
    };

    // Конфиги всех клеток
    struct Field {
        sf::Font font;
        std::vector<PathogenCell *> pathogens;
        std::vector<BodyCell *> bodies;
        std::vector<MacroCell *> macroes;
        std::vector<NeutroCell *> neutroes;
        std::vector<BCell *> bCells;
        std::vector<PlasmaCell *> plasmas;
        std::vector<Antibody *> antis;
        Temperature temperature;
        GameMenu menu;
    };
}

#endif //ECOSYSTEM_UTILS_H
