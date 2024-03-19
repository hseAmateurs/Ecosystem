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
void templateInit(std::vector<T *> &cells, const Assets::CellParam &cellParam) {
    sf::Vector2f pos;
    for (int i = 0; i < cellParam.amount; ++i) {
        T *cell = new T(cellParam);

        if (cell->type() == CellType::PLASMA) {
            pos.x = std::cos(M_PI / 4) * (PLASMA_DISTANCE * BRAIN_RADIUS);
            pos.y = SCREEN_HEIGHT - pos.x;
            pos.x = SCREEN_WIDTH - pos.x;
        }
        else if (cell->type() == CellType::BCELL)
            pos = brain::getXY(i, cellParam.amount);
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
    for (auto &param: Assets::instance().cellParams)
        createCells(param);
}

void Field::createCells(Assets::CellParam &cellParam, int amount) {
    cellParam.amount = amount;
    createCells(cellParam);
}


void Field::createCells(Assets::CellParam &cellParam) {
    switch (cellParam.cellType) {
        case utils::PATHOGEN:
            templateInit(pathogens, cellParam);
            break;
        case utils::BODY:
            templateInit(bodies, cellParam);
            break;
        case utils::MACRO:
            templateInit(macroes, cellParam);
            break;
        case utils::NEUTRO:
            templateInit(neutroes, cellParam);
            break;
        case utils::BCELL:
            templateInit(bCells, cellParam);
            break;
        case utils::PLASMA:
            templateInit(plasmas, cellParam);
            break;
        case utils::ANTI:
            templateInit(antis, cellParam);
            break;
    }
}

void Field::update() {
    randomlyPathogenSpawn();

    bodies.insert(bodies.end(), newBodies.begin(), newBodies.end());
    pathogens.insert(pathogens.end(), newPathogens.begin(), newPathogens.end());
    newPathogens.clear();
    newBodies.clear();
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

void Field::randomlyPathogenSpawn() {
    if(rand()%settings::RAND_SPAWN_PATHOGEN_ITER) return;

    if(DIFFICULT < '~' && rand()%settings::RAND_INC_DIFFICULT_AFTER_PATHOGEN_SPAWN==0)
        ++DIFFICULT;

    createCells(Assets::instance().cellParams[CellType::PATHOGEN], 1);
}
