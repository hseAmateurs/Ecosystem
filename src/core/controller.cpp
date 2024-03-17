#include "controller.h"
#include "assets.h"


Controller::Controller(WindowRender *windowRender, const Temperature *temperature) :
        pathogenTexture(texture::pathogen, sf::Color(139, 0, 255), 80,
                        {settings::SCREEN_WIDTH * 0.1, settings::SCREEN_HEIGHT * 0.9}, 720),
        bodyTexture(texture::bodyCell, sf::Color::Red,
                    70, {settings::SCREEN_WIDTH * 0.1, settings::SCREEN_HEIGHT * 0.1}, 720),
        bcellTexture(texture::bCell, sf::Color::Cyan,
                     70, {settings::SCREEN_WIDTH * 0.44, settings::SCREEN_HEIGHT * 0.4}, 720),
        macroTexture(texture::macrophage, sf::Color::Yellow,
                     120, {settings::SCREEN_WIDTH * 0.9, settings::SCREEN_HEIGHT * 0.9}, 720),
        plasmaTexture(texture::plasmaCell, sf::Color::Magenta,
                      150, {settings::SCREEN_WIDTH * 0.8, settings::SCREEN_HEIGHT * 0.1}, 720),
        m_temp(temperature), m_windowRender(windowRender),
        m_thread(&Controller::endGame, this) {
    textMain.setFont(Assets::instance().font);
    textMain.setString("GAME OVER");
    textMain.setPosition(settings::SCREEN_WIDTH * 0.125, settings::SCREEN_HEIGHT * 0.1f);
    textMain.setCharacterSize(settings::SCREEN_HEIGHT * 0.25f);

    textTime.setFont(Assets::instance().font);
    textTime.setPosition(settings::SCREEN_WIDTH * 0.22, settings::SCREEN_HEIGHT * 0.5f);
    textTime.setCharacterSize(settings::SCREEN_HEIGHT * 0.07f);
}

void Controller::run() {
    timeCounter.restart();
    m_windowRender->start();
    while (m_windowRender->window().isOpen()) {
        sf::Event event;
        while (m_windowRender->window().pollEvent(event))
            if (event.type == sf::Event::Closed) {
                // Останавливаем поток и дожидаемся его завершения
                if (m_windowRender->isRun()) m_windowRender->stop();
                if (runEnd) stopEndGame();
                m_windowRender->window().close();
            }
        if (m_temp->isCritical() && !runEnd) startEndGame();
        sf::sleep(sf::milliseconds(80));
    }
}

void Controller::startEndGame() {
    m_windowRender->stop();
    setIngameTime();
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
    }
}