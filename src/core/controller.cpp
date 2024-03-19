#include <iomanip>
#include <string>
#include <sstream>

#include "controller.h"
#include "assets.h"


Controller::Controller(WindowRender *windowRender, const Temperature *temperature) :
        pathogenTexture(texture::pathogen, settings::color::PATHOGEN, 80,
                        {settings::SCREEN_WIDTH * 0.1, settings::SCREEN_HEIGHT * 0.9}, 720),
        bodyTexture(texture::bodyCell, settings::color::BODY,
                    70, {settings::SCREEN_WIDTH * 0.1, settings::SCREEN_HEIGHT * 0.1}, 720),
        bcellTexture(texture::bCell, settings::color::BCELL,
                     70, {settings::SCREEN_WIDTH * 0.44, settings::SCREEN_HEIGHT * 0.4}, 720),
        macroTexture(texture::macrophage, settings::color::MACRO,
                     120, {settings::SCREEN_WIDTH * 0.9, settings::SCREEN_HEIGHT * 0.9}, 720),
        plasmaTexture(texture::plasmaCell, settings::color::PLASMA,
                      150, {settings::SCREEN_WIDTH * 0.8, settings::SCREEN_HEIGHT * 0.1}, 720),
        m_temp(temperature), m_windowRender(windowRender),
        m_thread(&Controller::endGame, this) {
    textMain.setFont(Assets::instance().font);
    textMain.setString("GAME OVER");
    textMain.setPosition(settings::SCREEN_WIDTH * 0.125, settings::SCREEN_HEIGHT * 0.1f);
    textMain.setCharacterSize(settings::SCREEN_HEIGHT * 0.25f);

    textTime.setFont(Assets::instance().font);
    textTime.setPosition(settings::SCREEN_WIDTH * 0.20, settings::SCREEN_HEIGHT * 0.5f);
    textTime.setCharacterSize(settings::SCREEN_HEIGHT * 0.07f);

    textDifc.setFont(Assets::instance().font);
    textDifc.setPosition(settings::SCREEN_WIDTH * 0.28, settings::SCREEN_HEIGHT * 0.58f);
    textDifc.setFillColor(sf::Color(240,180,0));
    textDifc.setCharacterSize(settings::SCREEN_HEIGHT * 0.05f);

    textInfo.setFont(Assets::instance().font);
    textInfo.setString("Press ENTER to restart the game");
    textInfo.setPosition(settings::SCREEN_WIDTH * 0.24, settings::SCREEN_HEIGHT * 0.7f);
    textInfo.setCharacterSize(settings::SCREEN_HEIGHT * 0.05f);
}

void Controller::run() {
    sf::Event event;
    timeCounter.restart();
    m_windowRender->start();
    while (m_windowRender->window().isOpen()) {
        if (m_temp->isCritical() && !runEnd) startEndGame();
        while (m_windowRender->window().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Останавливаем поток и дожидаемся его завершения
                if (m_windowRender->isRun()) m_windowRender->stop();
                if (runEnd) stopEndGame();
                m_windowRender->window().close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Enter) restartGame();
            }
        }
        sf::sleep(sf::milliseconds(80));
    }
}

void Controller::restartGame() {
    stopEndGame();
    m_windowRender->restart();
}

void Controller::startEndGame() {
    m_windowRender->stop();
    setIngameTime();
    setReachedDifficult();
    runEnd = true;
    m_thread.launch();
}

void Controller::stopEndGame() {
    runEnd = false;
    m_thread.wait();
}

void Controller::endGame() {
    m_windowRender->window().setActive(true);
    sf::Time elapsed;
    while (runEnd) {
        m_windowRender->window().clear(sf::Color(0, 100, 100));
        elapsed = timeCounter.restart();

        pathogenTexture.update(elapsed);
        bodyTexture.update(elapsed);
        bcellTexture.update(elapsed);
        macroTexture.update(elapsed);
        plasmaTexture.update(elapsed);

        m_windowRender->window().draw(pathogenTexture);
        m_windowRender->window().draw(bodyTexture);
        m_windowRender->window().draw(bcellTexture);
        m_windowRender->window().draw(macroTexture);
        m_windowRender->window().draw(plasmaTexture);

        m_windowRender->window().draw(textMain);
        m_windowRender->window().draw(textTime);
        m_windowRender->window().draw(textInfo);
        m_windowRender->window().draw(textDifc);

        m_windowRender->window().display();
    }
}

void Controller::setIngameTime() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << timeCounter.getElapsedTime().asSeconds();
    textTime.setString("Ingame Time = " + ss.str() + " seconds");
}

void Controller::setReachedDifficult() {
    textDifc.setString("Pathogens evolution " + std::to_string(Field::getDifficult() - '!') + '/' + std::to_string('~'-'!'));
}
