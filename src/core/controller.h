#ifndef ECOSYSTEM_CONTROLLER_H
#define ECOSYSTEM_CONTROLLER_H


#include <SFML/Graphics.hpp>

#include "../utils/settings.h"
#include "../textures/animations.h"
#include "../textures/cellTexture.h"
#include "windowRender.h"
#include "temperature.h"
#include "field.h"

class Controller {
public:
    Controller(WindowRender *windowRender, const Temperature *temperature);

    void run();

private:
    void setIngameTime();

    void setReachedDifficult();

    void endGame();

    void startEndGame();

    void stopEndGame();

    void restartGame();

    bool runEnd;

    const Temperature *m_temp;
    WindowRender *m_windowRender;

    sf::Thread m_thread;
    sf::Clock timeCounter;

    sf::Text textTime;
    sf::Text textMain;
    sf::Text textInfo;
    sf::Text textDifc;

    texture::CellTexture pathogenTexture;
    texture::CellTexture bodyTexture;
    texture::CellTexture bcellTexture;
    texture::CellTexture macroTexture;
    texture::CellTexture plasmaTexture;
};

#endif //ECOSYSTEM_CONTROLLER_H
