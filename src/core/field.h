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

// Хранение объектов на поле
class Field {
public:
    ~Field();

    void init();

    void free();

    // Отрисовка конкретного типа клетки
    void createCells(const Assets::CellParam &cellParam) { createCells(cellParam, cellParam.amount); }

    void createCells(const Assets::CellParam &cellParam, int amount);

    static int getDifficult() { return DIFFICULT; }

    void update();

    void spawnImmuneCells(const sf::Time &deltaTime);

    void spawnPathogens();

    std::vector<PathogenCell *> pathogens;
    std::vector<BodyCell *> bodies;
    std::vector<MacroCell *> macroes;
    std::vector<NeutroCell *> neutroes;
    std::vector<BCell *> bCells;
    std::vector<PlasmaCell *> plasmas;
    std::vector<Antibody *> antis;

    std::vector<PathogenCell *> newPathogens;
    std::vector<BodyCell *> newBodies;
    std::vector<NeutroCell *> newNeutroes;
    std::vector<MacroCell *> newMacroes;

    // Время до следующей итерации спавна клеток
    sf::Time macroSpawnTime;
    sf::Time neutroSpawnTime;

    // 33 -> 126
    static int DIFFICULT;
};


#endif //ECOSYSTEM_FIELD_H
