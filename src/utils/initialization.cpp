//
// Created by Shon on 21.02.2024.
//

#include "initialization.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include "settings.h"
#include "brain.h"

using namespace settings;


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
                config[cellType].animation = texture::pathogen;
                break;
            case BODY:
                config[cellType].color = sf::Color::Red;
                config[cellType].animation = texture::bodyCell;
                break;
            case MACRO:
                config[cellType].color = sf::Color::Yellow;
                config[cellType].animation = texture::macrophage;
                break;
            case NEUTRO:
                config[cellType].color = sf::Color::Green;
                config[cellType].animation = texture::neutrophil;
                break;
            case BCELL:
                config[cellType].color = sf::Color::Cyan;
                config[cellType].animation = texture::bCell;
                break;
            case PLASMA:
                config[cellType].color = sf::Color::Magenta;
                config[cellType].animation = texture::plasmaCell;
                break;
            case ANTI:
                config[cellType].color = sf::Color::Yellow;
                config[cellType].animation = texture::antibody;
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

utils::Field utils::initField(const vector<utils::CellParam> &config, const std::string &fontPath, sf::RenderWindow &window) {
    utils::Field field;

    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Can't load font\n";
        exit(-1);
    }
    field.font = font;

    size_t configSize = config.size();
    for (int i = 0; i < configSize; ++i) {
        switch (i) {
            case PATHOGEN:
                createCells(field.pathogens, config[i], window);
                break;
            case BODY:
                createCells(field.bodies, config[i], window);
                break;
            case MACRO:
                createCells(field.macroes, config[i], window);
                break;
            case NEUTRO:
                createCells(field.neutroes, config[i], window);
                break;
            case BCELL:
                createCells(field.bCells, config[i], window);
                break;
            case PLASMA:
                createCells(field.plasmas, config[i], window);
                break;
            case ANTI:
                createCells(field.antis, config[i], window);
                break;
            default:
                std::cerr << "Undefined cell type\n";
        }
    }

    return field;
}

template<class T>
void utils::createCells(vector <T*> &cells, const utils::CellParam &param, sf::RenderWindow &window) {
    sf::Vector2u windowSize = window.getSize();

    for (int i = 0; i < param.amount; ++i) {
        float posX, posY;
        do {
            posX = rand() % (windowSize.x - 2 * static_cast<int>(param.radius));
            posY = rand() % (windowSize.y - 2 * static_cast<int>(param.radius));
        } while ((posY - SCREEN_HEIGHT) * (posY - SCREEN_HEIGHT) + (posX - SCREEN_WIDTH) * (posX - SCREEN_WIDTH) <
                 BRAIN_RADIUS * BRAIN_RADIUS); // this will be a problem later on. i don't care.
        T *cell = new T(param.animation, param.radius, param.size, param.speed, {posX, posY}, param.color);

        if (cell->type() == CellType::PLASMA) {
            posX = std::cos(M_PI / 4) * (PLASMA_DISTANCE * BRAIN_RADIUS);
            posY = posX;
            cell->setPosition(SCREEN_WIDTH - posX, SCREEN_HEIGHT - posY);
        }
        else if (cell->type() == CellType::BCELL)
            cell->setPosition(brain::getXY(i, param.amount));
        window.draw(*cell);
        cells.push_back(cell);
    }
}
