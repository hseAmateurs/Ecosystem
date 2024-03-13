//
// Created by Shon on 13.03.2024.
//

#ifndef ECOSYSTEM_ASSETS_H
#define ECOSYSTEM_ASSETS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

#include "../textures/animations.h"
#include "../utils/cellTypes.h"

using utils::CellType;

class Assets {
public:
    Assets(Assets const &) = delete;

    Assets &operator=(Assets const &) = delete;

    static Assets &instance() {
        static Assets s;
        return s;
    }

    void loadConfig(const std::string &fileName);

    void loadFont(const std::string &fileName);

    // Конфиг клетки
    struct CellParam {
        CellParam() :
                radius(0), size(0), speed(0), amount(0),
                color(sf::Color::Black),
                animation(texture::bodyCell) { };

        float radius;
        int size;
        float speed;
        int amount;
        sf::Color color;
        texture::AnimationParameters animation;
    };

    sf::Font font;

    std::vector<CellParam> cellParams;

private:
    std::map<std::string, CellType> mapTypes;

    Assets();

    ~Assets() { };
};


#endif //ECOSYSTEM_ASSETS_H
