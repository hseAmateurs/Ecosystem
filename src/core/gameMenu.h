#ifndef ECOSYSTEM_GAMEMENU_H
#define ECOSYSTEM_GAMEMENU_H


#include <SFML/Graphics.hpp>
#include "../utils/settings.h"
#include <sstream>
#include "../textures/cellTexture.h"
#include "../textures/animations.h"


class GameMenu {
public:
    GameMenu() :
            pathogenTexture(texture::pathogen, sf::Color(139, 0, 255), 80,
                            {settings::SCREEN_WIDTH * 0.1, settings::SCREEN_HEIGHT * 0.9}, 720),
            bodyTexture(texture::bodyCell, sf::Color::Red,
                        70, {settings::SCREEN_WIDTH * 0.1, settings::SCREEN_HEIGHT * 0.1}, 720),
            bcellTexture(texture::bCell, sf::Color::Cyan,
                         70, {settings::SCREEN_WIDTH * 0.44, settings::SCREEN_HEIGHT * 0.4}, 720),
            macroTexture(texture::macrophage, sf::Color::Yellow,
                         120, {settings::SCREEN_WIDTH * 0.9, settings::SCREEN_HEIGHT * 0.9}, 720),
            plasmaTexture(texture::plasmaCell, sf::Color::Magenta,
                          150, {settings::SCREEN_WIDTH * 0.8, settings::SCREEN_HEIGHT * 0.1}, 720) { }

    void endGame(sf::RenderWindow &window, const sf::Font &font, sf::Time elapsed);

    void update(sf::Time elapsed) { inGameTime += elapsed; }

private:
    sf::Text text;
    sf::Time inGameTime;
    texture::CellTexture pathogenTexture;
    texture::CellTexture bodyTexture;
    texture::CellTexture bcellTexture;
    texture::CellTexture macroTexture;
    texture::CellTexture plasmaTexture;
};

#endif //ECOSYSTEM_GAMEMENU_H
