//
// Created by Shon on 13.03.2024.
//

#ifndef ECOSYSTEM_FIELD_H
#define ECOSYSTEM_FIELD_H

#include <vector>

#include "assets.h"

class BCell;

class BodyCell;

class PathogenCell;

class MacroCell;

class PlasmaCell;

class NeutroCell;

class Antibody;

class Temperature;

// Хранение объектов на поле
class Field {
public:
    ~Field();

    void init();

    // Отрисовка конкретного типа клетки
    void createCells(const Assets::CellParam &cellParam);

    std::vector<PathogenCell *> pathogens;
    std::vector<BodyCell *> bodies;
    std::vector<MacroCell *> macroes;
    std::vector<NeutroCell *> neutroes;
    std::vector<BCell *> bCells;
    std::vector<PlasmaCell *> plasmas;
    std::vector<Antibody *> antis;
};


#endif //ECOSYSTEM_FIELD_H
