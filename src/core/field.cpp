//
// Created by Shon on 13.03.2024.
//

#include "field.h"
#include "../utils/settings.h"
#include "../utils/brain.h"
#include "../utils/cells.h"

using namespace settings;

int Field::DIFFICULT = '!';

// Функция вне класса для создания клеток
template<class T>
void templateInit(std::vector<T *> &cells, const Assets::CellParam &cellParam, const int amount) {
    sf::Vector2f pos;
    for (int i = 0; i < amount; ++i) {
        T *cell = new T(cellParam);

        if (cell->type() == CellType::PLASMA) {
            pos.x = std::cos(M_PI / 4) * (PLASMA_DISTANCE * BRAIN_RADIUS);
            pos.y = SCREEN_HEIGHT - pos.x;
            pos.x = SCREEN_WIDTH - pos.x;
        }
        else if (cell->type() == CellType::BCELL)
            pos = brain::getXY(i, amount);
        else {
            do {
                pos.x = rand() % (SCREEN_WIDTH - 2 * static_cast<int>(cellParam.radius));
                pos.y = rand() % (SCREEN_HEIGHT - 2 * static_cast<int>(cellParam.radius));
            } while ((pos.y - SCREEN_HEIGHT) * (pos.y - SCREEN_HEIGHT) +
                     (pos.x - SCREEN_WIDTH) * (pos.x - SCREEN_WIDTH) <
                     BRAIN_RADIUS * BRAIN_RADIUS);
        }
        cell->setPosition(pos);
        cells.push_back(cell);
    }
}

// Функция вне класса для удаления вектора клеток
template<class T>
void templateFree(std::vector<T *> &cells) {
    for (T *&cell: cells)
        delete cell;
    cells.clear();
}


void Field::init() {
    macroSpawnTime = MACRO_SPAWN_TIME;
    neutroSpawnTime = NEUTRO_SPAWN_TIME;

    for (auto &param: Assets::instance().cellParams)
        createCells(param);
}

void Field::createCells(const Assets::CellParam &cellParam, int amount) {
    switch (cellParam.cellType) {
        case utils::PATHOGEN:
            templateInit(pathogens, cellParam, amount);
            break;
        case utils::BODY:
            templateInit(bodies, cellParam, amount);
            break;
        case utils::MACRO:
            templateInit(macroes, cellParam, amount);
            break;
        case utils::NEUTRO:
            templateInit(neutroes, cellParam, amount);
            break;
        case utils::BCELL:
            templateInit(bCells, cellParam, amount);
            break;
        case utils::PLASMA:
            templateInit(plasmas, cellParam, amount);
            break;
        case utils::ANTI:
            templateInit(antis, cellParam, amount);
            break;
    }
}

void Field::update() {
    spawnPathogens();

    bodies.insert(bodies.end(), newBodies.begin(), newBodies.end());
    pathogens.insert(pathogens.end(), newPathogens.begin(), newPathogens.end());
    neutroes.insert(neutroes.end(), newNeutroes.begin(), newNeutroes.end());
    macroes.insert(macroes.end(), newMacroes.begin(), newMacroes.end());

    newPathogens.clear();
    newBodies.clear();
    newNeutroes.clear();
    newMacroes.clear();
}

Field::~Field() {
    free();
}

void Field::free() {
    templateFree(bCells);
    templateFree(pathogens);
    templateFree(bodies);
    templateFree(macroes);
    templateFree(neutroes);
    templateFree(plasmas);
    templateFree(antis);
}


void Field::spawnImmuneCells(const sf::Time &deltaTime) {
    if (macroSpawnTime <= sf::Time::Zero) {
        auto *newMacro = new MacroCell(Assets::instance().cellParams[CellType::MACRO]);
        newMacro->setPosition(SPAWN_POS[rand() % 3]);
        newMacroes.push_back(newMacro);
        macroSpawnTime = MACRO_SPAWN_TIME;
    }

    if (neutroSpawnTime <= sf::Time::Zero) {
        auto *newNeutro = new NeutroCell(Assets::instance().cellParams[CellType::NEUTRO]);
        newNeutro->setPosition(SPAWN_POS[rand() % 3]);
        newNeutroes.push_back(newNeutro);
        neutroSpawnTime = NEUTRO_SPAWN_TIME;
    }

    macroSpawnTime -= deltaTime;
    neutroSpawnTime -= deltaTime;
}

void Field::spawnPathogens() {
    if (rand() % settings::RAND_SPAWN_PATHOGEN_ITER) return;

    if (DIFFICULT < '~' && rand() % settings::RAND_INC_DIFFICULT_AFTER_PATHOGEN_SPAWN == 0)
        ++DIFFICULT;

    createCells(Assets::instance().cellParams[CellType::PATHOGEN], 1);
}
