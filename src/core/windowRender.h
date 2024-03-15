//
// Created by Shon on 13.03.2024.
//

#ifndef ECOSYSTEM_WINDOWRENDER_H
#define ECOSYSTEM_WINDOWRENDER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "field.h"

// Рендер игры
class WindowRender {
public:
    explicit WindowRender(Field *field) :
            m_field(field), m_thread(&WindowRender::render, this) { init(); };

    bool isRun() const { return run; };

    void start();

    void stop();

private:
    void init();

    void render();

    template<class T>
    void drawCells(std::vector<T *> &cells);

    void drawField();

    bool run;

    Field *m_field;
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
