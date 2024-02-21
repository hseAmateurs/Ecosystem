//
// Created by Shon on 21.02.2024.
//

#ifndef ECOSYSTEM_INITIALIZATION_H
#define ECOSYSTEM_INITIALIZATION_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../objects/pathogenCell.h"
#include "../objects/bodyCell.h"
#include "../objects/macroCell.h"
#include "../objects/neutroCell.h"

using std::vector;

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
    vector<PathogenCell> pathogens;
    vector<BodyCell> bodies;
    vector<MacroCell> macroes;
    vector<NeutroCell> neutroes;
} Field;

vector<CellParam> readCSV(const std::string &fileName);

// Начальная отрисовка всех клеток на поле
Field initField(const vector<CellParam> &config, sf::RenderWindow &window);

// Отрисовка конкретного типа клетки
template<class T>
vector<T> createCells(const CellParam &param, sf::RenderWindow &window);

#endif //ECOSYSTEM_INITIALIZATION_H
