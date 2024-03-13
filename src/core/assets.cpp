//
// Created by Shon on 13.03.2024.
//

#include "assets.h"

#include <fstream>
#include <sstream>


Assets::Assets() {
    mapTypes["pathogen"] = CellType::PATHOGEN;
    mapTypes["body"] = CellType::BODY;
    mapTypes["macro"] = CellType::MACRO;
    mapTypes["neutro"] = CellType::NEUTRO;
    mapTypes["bcell"] = CellType::BCELL;
    mapTypes["plasma"] = CellType::PLASMA;
    mapTypes["anti"] = CellType::ANTI;

    cellParams.resize(CellType::COUNT);
}

void Assets::loadConfig(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) throw;

    std::string line;
    std::string token;
    std::vector<std::string> tokens;

    CellType cellType;
    CellParam param;
    const int argsCount = 4;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        while (std::getline(ss, token, ';'))
            tokens.push_back(token);

        try {
            cellType = mapTypes.at(tokens[0]);
        } catch (const std::out_of_range &ex) {
            // Пропускаем, если не найден ключ
            continue;
        }

        if (tokens.size() != argsCount)
            throw std::length_error("Wrong arguments count");

        param.cellType = cellType;
        param.radius = std::stof(tokens[1]);
        param.size = std::stoi(tokens[2]);
        param.speed = std::stof(tokens[3]);
        param.amount = std::stoi(tokens[4]);

        switch (cellType) {
            case CellType::PATHOGEN:
                param.color = sf::Color(139, 0, 255);
                param.animation = texture::pathogen;
                break;
            case CellType::BODY:
                param.color = sf::Color::Red;
                param.animation = texture::bodyCell;
                break;
            case CellType::MACRO:
                param.color = sf::Color::Yellow;
                param.animation = texture::macrophage;
                break;
            case CellType::NEUTRO:
                param.color = sf::Color::Green;
                param.animation = texture::neutrophil;
                break;
            case CellType::BCELL:
                param.color = sf::Color::Cyan;
                param.animation = texture::bCell;
                break;
            case CellType::PLASMA:
                param.color = sf::Color::Magenta;
                param.animation = texture::plasmaCell;
                break;
            case CellType::ANTI:
                param.color = sf::Color(219, 112, 147);
                param.animation = texture::antibody;
                break;
            default:
                throw std::runtime_error("Undefined cell type");
        }

        cellParams[cellType] = param;
        tokens.clear();
    }
    file.close();
}

void Assets::loadFont(const std::string &fileName) {
    if (!font.loadFromFile(fileName))
        throw std::runtime_error("Can't load font");
}
