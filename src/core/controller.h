#ifndef ECOSYSTEM_CONTROLLER_H
#define ECOSYSTEM_CONTROLLER_H


#include <SFML/Graphics.hpp>

#include "../utils/settings.h"
#include "../textures/animations.h"
#include "../textures/cellTexture.h"
#include "windowRender.h"
#include "temperature.h"

class Controller {
public:
    Controller(WindowRender *windowRender, const Temperature *temperature);

    void run();

private:
    void setIngameTime();

    void endGame();

    void startEndGame();

    void stopEndGame();

    bool runEnd;

    const Temperature *m_temp;
    WindowRender *m_windowRender;

    sf::Thread m_thread;
    sf::Clock timeCounter;

    sf::Text textTime;
    sf::Text textMain;
    texture::CellTexture pathogenTexture;
    texture::CellTexture bodyTexture;
    texture::CellTexture bcellTexture;
    texture::CellTexture macroTexture;
    texture::CellTexture plasmaTexture;
};

#endif //ECOSYSTEM_CONTROLLER_H
