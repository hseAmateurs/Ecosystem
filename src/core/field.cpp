//
// Created by Shon on 13.03.2024.
//

#include "field.h"
#include "../utils/settings.h"
#include "../utils/brain.h"
#include "../utils/cells.h"

using namespace settings;

// Функция вне класса для создания клеток
template<class T>
void templateInit(T* cell, const Assets::CellParam &cellParam) {
    float posX, posY;
    for (int i = 0; i < cellParam.amount; ++i) {
        do {
            posX = rand() % (SCREEN_WIDTH - 2 * static_cast<int>(cellParam.radius));
            posY = rand() % (SCREEN_HEIGHT - 2 * static_cast<int>(cellParam.radius));
        } while ((posY - SCREEN_HEIGHT) * (posY - SCREEN_HEIGHT) + (posX - SCREEN_WIDTH) * (posX - SCREEN_WIDTH) <
                 BRAIN_RADIUS * BRAIN_RADIUS);

        cell = new T(cellParam.animation, cellParam.radius,
                     cellParam.size, cellParam.speed, {posX, posY}, cellParam.color);

        if (cell->type() == CellType::PLASMA) {
            posX = std::cos(M_PI / 4) * (PLASMA_DISTANCE * BRAIN_RADIUS);
            posY = posX;
            cell->setPosition(SCREEN_WIDTH - posX, SCREEN_HEIGHT - posY);
        }
        else if (cell->type() == CellType::BCELL)
            cell->setPosition(brain::getXY(i, cellParam.amount));
    }
}
// Функция вне класса для удаления вектора клеток
template<class T>
void templateFree(std::vector<T *> cells) {
    for (T *&cell: cells)
        delete cell;
}


void Field::init() {
    for (auto &param: Assets::instance().cellParams)
        createCells(param);
}

void Field::createCells(const Assets::CellParam &cellParam) {
    switch (cellParam.cellType) {
        case utils::PATHOGEN:
            PathogenCell *pathogen;
            templateInit(pathogen, cellParam);
            break;
        case utils::BODY:
            BodyCell *bodyCell;
            templateInit(bodyCell, cellParam);
            break;
        case utils::MACRO:
            MacroCell *macro;
            templateInit(macro, cellParam);
            break;
        case utils::NEUTRO:
            NeutroCell *neutro;
            templateInit(neutro, cellParam);
            break;
        case utils::BCELL:
            BCell *bCell;
            templateInit(bCell, cellParam);
            break;
        case utils::PLASMA:
            PlasmaCell *plasma;
            templateInit(plasma, cellParam);
            break;
        case utils::ANTI:
            PlasmaCell *anti;
            templateInit(anti, cellParam);
            break;
    }
}

Field::~Field() {
    templateFree(bCells);
    templateFree(pathogens);
    templateFree(bodies);
    templateFree(macroes);
    templateFree(neutroes);
    templateFree(plasmas);
    templateFree(antis);
}
