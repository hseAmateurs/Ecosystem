//
// Created by Shon on 13.03.2024.
//

#include <iostream>

#include "windowRender.h"
#include "../utils/cells.h"


void WindowRender::render() {
    m_window.setActive(true);

    // For debugging ---
    sf::CircleShape brain(settings::BRAIN_RADIUS);
    brain.setFillColor(sf::Color::Black);
    brain.setOrigin(settings::BRAIN_RADIUS, settings::BRAIN_RADIUS);
    brain.setPosition(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT);
    // ---

    while (isRun()) {
        m_window.clear(sf::Color::White);
        deltaTime = clock.restart();

        m_window.draw(brain);
        drawField();

        m_window.display();
    }
}

void WindowRender::drawField() {
    drawCells(m_field->pathogens);

    m_field->updateBodyCell(deltaTime);
    drawCells(m_field->bodies);

    drawCells(m_field->macroes);

    drawCells(m_field->neutroes);

    drawCells(m_field->bCells);

    drawCells(m_field->plasmas);

    drawCells(m_field->antis);
}

void WindowRender::init() {
    m_window.create(sf::VideoMode(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT), "Ecosystem",
                    sf::Style::Titlebar | sf::Style::Close);
    m_window.setVerticalSyncEnabled(true);
    m_window.setActive(false);
}

void WindowRender::start() {
    run = true;
    m_thread.launch();

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                // Останавливаем поток и дожидаемся его завершения
                stop();
    }
}

void WindowRender::stop() {
    run = false;
    m_thread.wait();
    m_window.close();
}
