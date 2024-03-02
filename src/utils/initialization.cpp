//
// Created by Shon on 21.02.2024.
//

#include "initialization.h"

#include <sstream>
#include <iostream>
#include <fstream>


vector<utils::CellParam> utils::readCSV(const std::string &fileName) {
    vector<utils::CellParam> config;

    std::ifstream file(fileName);
    std::string line;

    std::string token;
    std::vector<std::string> tokens;

    int cellType = 0;
    utils::CellParam param;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        while (std::getline(ss, token, ';'))
            tokens.push_back(token);

        if (tokens.size() != 4) {
            std::cerr << "Wrong args number" << std::endl;
            continue;
        }
        param.radius = std::stof(tokens[0]);
        param.size = std::stoi(tokens[1]);
        param.speed = std::stof(tokens[2]);
        param.amount = std::stoi(tokens[3]);
        config.push_back(param);
        switch (cellType) {
            case PATHOGEN:
                config[cellType].color = sf::Color(139, 0, 255);
                break;
            case BODY:
                config[cellType].color = sf::Color::Red;
                break;
            case MACRO:
                config[cellType].color = sf::Color::Yellow;
                break;
            case NEUTRO:
                config[cellType].color = sf::Color::Green;
                break;
            default:
                std::cerr << "Undefined cell type\n";
        }
        cellType++;

        tokens.clear();
    }
    file.close();

    return config;
}

utils::Field utils::initField(const vector<utils::CellParam> &config, sf::RenderWindow &window) {
    srand(time(0));
    utils::Field field;

    size_t configSize = config.size();
    for (int i = 0; i < configSize; ++i) {
        switch (i) {
            case PATHOGEN:
                field.pathogens = createCells<PathogenCell>(config[i], window);
                break;
            case BODY:
                field.bodies = createCells<BodyCell>(config[i], window);
                break;
            case MACRO:
                field.macroes = createCells<MacroCell>(config[i], window);
                break;
            case NEUTRO:
                field.neutroes = createCells<NeutroCell>(config[i], window);
                break;
            default:
                std::cerr << "Undefined cell type\n";
        }
    }

    return field;
}

template<class T>
vector<T> utils::createCells(const utils::CellParam &param, sf::RenderWindow &window) {
    vector<T> cells;

    sf::Vector2u windowSize = window.getSize();
    for (int i = 0; i < param.amount; ++i) {
        float posX, posY;
        do {
            posX = rand() % (windowSize.x - 2 * static_cast<int>(param.radius));
            posY = rand() % (windowSize.y - 2 * static_cast<int>(param.radius));
        } while ((posY - 900.f) * (posY - 900.f) + (posX - 1600.f) * (posX - 1600.f) <
                 400030); // this will be a problem later on. i don't care.
        T cell(param.radius, param.size, param.speed, {posX, posY}, param.color);
        window.draw(cell);
        cells.push_back(cell);
    }
    return cells;
}
