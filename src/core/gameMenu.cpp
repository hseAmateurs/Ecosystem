#include "gameMenu.h"


void GameMenu::endGame(sf::RenderWindow &window, const sf::Font &font, sf::Time elapsed) {
    pathogenTexture.update(elapsed);
    bodyTexture.update(elapsed);
    bcellTexture.update(elapsed);
    macroTexture.update(elapsed);
    plasmaTexture.update(elapsed);

    window.draw(pathogenTexture);
    window.draw(bodyTexture);
    window.draw(bcellTexture);
    window.draw(macroTexture);
    window.draw(plasmaTexture);


    text.setString("GAME OVER");
    text.setPosition(settings::SCREEN_WIDTH * 0.125, settings::SCREEN_HEIGHT * 0.1f);
    text.setCharacterSize(settings::SCREEN_HEIGHT * 0.25f);
    text.setFont(font);
    window.draw(text);

    std::ostringstream ss;
    ss << inGameTime.asSeconds();

    text.setString("Ingame Time = " + ss.str().substr(0, 3) + " seconds");
    text.setPosition(settings::SCREEN_WIDTH * 0.22, settings::SCREEN_HEIGHT * 0.5f);
    text.setCharacterSize(settings::SCREEN_HEIGHT * 0.07f);
    window.draw(text);
}
