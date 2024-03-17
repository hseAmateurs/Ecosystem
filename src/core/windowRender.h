//
// Created by Shon on 13.03.2024.
//

#ifndef ECOSYSTEM_WINDOWRENDER_H
#define ECOSYSTEM_WINDOWRENDER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "field.h"
#include "temperature.h"

// Рендер игры
class WindowRender {
public:
    explicit WindowRender(Field *field, Temperature *temp) :
            m_field(field), m_temp(temp), m_thread(&WindowRender::render, this) { init(); };

    sf::RenderWindow &window() { return m_window; };

    bool isRun() const { return run; };

    void start();

    void stop();

    void restart();

private:
    void init();

    void render();

    template<class T>
    void drawCells(std::vector<T *> &cells);

    void drawField();

    bool run;

    Field *m_field;
    Temperature *m_temp;
    sf::RenderWindow m_window;
    sf::Thread m_thread;

    sf::Clock clock;
    sf::Time deltaTime;
};

template<class T>
void WindowRender::drawCells(std::vector<T *> &cells) {
    int cellsSize = cells.size();
    for (int i = cellsSize - 1; i >= 0; --i) {
        auto &cell = cells[i];
        if (cell->isDead()) {
            delete cell;
            cells.erase(cells.begin() + i);
            continue;
        }
        cell->update(*m_field, deltaTime, m_window);
        m_window.draw(*cell);
    }
}


#endif //ECOSYSTEM_WINDOWRENDER_H
