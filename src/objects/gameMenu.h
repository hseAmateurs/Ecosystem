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
            pathogenTexture(texture::pathogen,{settings::SCREEN_WIDTH*0.1,settings::SCREEN_HEIGHT*0.9},80,720,sf::Color(139,0,255)),
            bodyTexture(texture::bodyCell,{settings::SCREEN_WIDTH*0.1,settings::SCREEN_HEIGHT*0.1},70,720,sf::Color::Red),
            bcellTexture(texture::bCell,{settings::SCREEN_WIDTH*0.44,settings::SCREEN_HEIGHT*0.4},70,720,sf::Color::Cyan),
            macroTexture(texture::macrophage,{settings::SCREEN_WIDTH*0.9,settings::SCREEN_HEIGHT*0.9},120,720,sf::Color::Yellow),
            plasmaTexture(texture::plasmaCell,{settings::SCREEN_WIDTH*0.8,settings::SCREEN_HEIGHT*0.1},150,720,sf::Color::Magenta)
    { }
    void endGame(sf::RenderWindow &window, const sf::Font& font, sf::Time elapsed);
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
