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
    if (!file.is_open()) throw std::runtime_error("Can't open config file");

    std::string line;
    std::string token;
    std::vector<std::string> tokens;

    CellType cellType;
    CellParam param;
    const int argsCount = 5;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        while (std::getline(ss, token, ';'))
            tokens.push_back(token);

        try {
            cellType = mapTypes.at(tokens[0]);
        } catch (const std::out_of_range &ex) {
            // Пропускаем, если не найден ключ
            tokens.clear();
            continue;
        }

        if (tokens.size() != argsCount)
            throw std::length_error("Wrong arguments count");

        param.cellType = cellType;
        param.radius = std::stof(tokens[1]);
        param.size = std::stoi(tokens[2]);
        param.speed = std::stof(tokens[3]);
        param.amount = std::stoi(tokens[4]);

        cellParams[cellType] = param;
        tokens.clear();
    }
    file.close();
}

void Assets::loadFont(const std::string &fileName) {
    if (!font.loadFromFile(fileName))
        throw std::runtime_error("Can't load font");
}
