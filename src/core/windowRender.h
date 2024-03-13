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
    explicit WindowRender(Field &field) :
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

    Field m_field;
    sf::RenderWindow m_window;
    sf::Thread m_thread;

    sf::Clock clock;
    sf::Time deltaTime;
};

template<class T>
void WindowRender::drawCells(std::vector<T *> &cells) {
    int cellsSize = cells.size();
    std::vector<int> deadCells;
    for (int i = 0; i < cellsSize; ++i) {
        auto &cell = cells[i];
        m_window.draw(*cell);
        if (cell->isDead()) {
            deadCells.push_back(i);
            continue;
        }
        cell->update(m_field, deltaTime);
        m_window.draw(*cell);
        cell->drawTexture(m_window, deltaTime);
    }
    // Подчищаем мертвые клетки
    int deadSize = deadCells.size();
    for (int i = deadSize - 1; i >= 0; --i) {
        delete cells[deadCells[i]];
        cells.erase(cells.begin() + deadCells[i]);
    }
}


#endif //ECOSYSTEM_WINDOWRENDER_H
