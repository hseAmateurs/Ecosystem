#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

#include "utils/initialization.h"
#include "utils/settings.h"
#include "utils/freeMemory.h"

using namespace utils;
using namespace settings;

bool isRun = true;

template<class T>
void drawing(vector<T*> &cells, Field &field, sf::RenderWindow &window, sf::Time &deltaTime) {
    int cellsSize = cells.size();
    vector<int> deadCells;
    for (int i = 0; i < cellsSize; ++i) {
        auto &cell = cells[i];
        if(cell->isDead()) {
            deadCells.push_back(i);
            continue;
        }
        cell->update(field, deltaTime);
        window.draw(*cell);
        cell->setFont(field.font);
        cell->drawTexture(window, deltaTime);
    }
    // Подчищаем мертвые клетки
    int deadSize = deadCells.size();
    for (int i = deadSize - 1; i >= 0; --i) {
        delete cells[deadCells[i]];
        cells.erase(cells.begin() + deadCells[i]);
    }
}

void renderingThread(sf::RenderWindow &window, Field &field) {
    window.setActive(true);
    sf::Clock clock;

    // For debugging ---
    sf::CircleShape brain(BRAIN_RADIUS);
    brain.setFillColor(sf::Color::Black);
    brain.setOrigin(BRAIN_RADIUS, BRAIN_RADIUS);
    brain.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::Time timer = sf::seconds(2);
    // ---

    while (isRun) {
        window.clear(sf::Color::White);
        window.draw(brain); // DEBUG
        sf::Time deltaTime = clock.restart();
        timer -= deltaTime;
        if(timer <= sf::Time::Zero) {
            timer = sf::seconds(120);
            std::cout << "Zero\n";
            delete field.bCells.back();
            field.bCells.pop_back();
        }

        for (int i = 0; i < CellType::COUNT; ++i) {
            switch (i) {
                case PATHOGEN:
//                    for (BodyCell *cell: field.bodies) {
//                        if (cell->texture.isDead()) {
//                            PathogenCell *newCell = new PathogenCell(texture::pathogen, field.pathogens[0]->getRadius(),field.pathogens[0]->getSize(),field.pathogens[0]->getSpeed(),cell->getPosition(),field.pathogens[0]->getColor());
//                            std::cout << "Create pathpgen\n";
//                            field.pathogens.push_back(newCell);
//                        }
//                    }
                    drawing(field.pathogens, field, window, deltaTime);
                    break;
                case BODY:
                    for (BodyCell *cell: field.bodies) {
                        if (cell->texture.isDead()){
                            PathogenCell *newCell = new PathogenCell(texture::pathogen, field.pathogens[0]->getRadius(), field.pathogens[0]->getSize(), field.pathogens[0]->getSpeed(), cell->getPosition(), field.pathogens[0]->getColor());
                            std::cout<<"Create pathpgen\n";
                            field.pathogens.push_back(newCell);
                        }
                        cell->cellDivision(deltaTime, field.bodies);
                    }
                    drawing(field.bodies, field, window, deltaTime);
                    break;
                case MACRO:
                    drawing(field.macroes, field, window, deltaTime);
                    break;
                case NEUTRO:
                    drawing(field.neutroes, field, window, deltaTime);
                    break;
                case BCELL:
                    drawing(field.bCells, field, window, deltaTime);
                    break;
                case PLASMA:
                    drawing(field.plasmas, field, window, deltaTime);
                    break;
                default:
                    std::cerr << "Undefined cell type\n";
            }
        }
        window.display();
    }
}

int main() {
    setbuf(stdout, nullptr);
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT), "Ecosystem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    Field field = initField(readCSV("../data.csv"), "../resources/font/couriercyrps_bold.ttf", window);

    // Отключаем контекст окна после инициалазиции поля
    window.setActive(false);

    // Запускаем поток рендринга
    sf::Thread thread(std::bind(&renderingThread, std::ref(window), std::ref(field)));
    thread.launch();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Останавливаем поток и дожидаемся его завершения
                isRun = false;
                thread.wait();
                window.close();
            }
        }
    }

    freeField(field);

    return 0;
}
