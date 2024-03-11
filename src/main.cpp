#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

#include "utils/initialization.h"
#include "utils/settings.h"
#include "utils/freeMemory.h"

using namespace utils;

bool isRun = true;

template<class T>
void drawing(vector<T *> &cells, Field &field, sf::RenderWindow &window, sf::Time &deltaTime) {
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
    bool stepOne = true;
    bool stepTwo = true;
    // ---

    while (isRun) {
        window.clear(sf::Color::White);
        vector<BodyCell *> newBodies;
// DEBUG ---
        window.draw(brain);
        sf::Time deltaTime = clock.restart();
        timer -= deltaTime;
        if (timer <= sf::Time::Zero && stepOne) {
            stepOne = false;
            field.bCells.front()->setStatus(BCell::BUSY);
            for (int i = 0; i < field.bCells.size(); ++i) {
                field.bCells[i]->setCode('s');
            }
//            field.macroes[0]->setCode('0');
//            field.macroes[0]->setPosition(1500, 300);
//            field.macroes[1]->setCode('1');
//            field.macroes[1]->setPosition(1400, 300);
//            field.macroes[2]->setCode('3');
//            field.macroes[2]->setPosition(1300, 300);
//            field.macroes[3]->setCode('4');
//            field.macroes[3]->setPosition(100, 300);
//            field.macroes[4]->setCode('1');
//            field.macroes[4]->setPosition(400, 300);
//            field.macroes[5]->setCode('0');
//            field.macroes[5]->setPosition(200, 300);
//            field.macroes[6]->setCode('4');
//            field.macroes[6]->setPosition(0, 300);
            for (int i = 0; i < field.macroes.size(); ++i) {
                field.macroes[i]->setPosition(1200, 300);
                field.macroes[i]->setStatus(MacroCell::DELIVERY);
                std::cout << "Start: " << field.macroes[i]->getCode() << "\n";
            }
//            field.bCells.front()->setStatus(BCell::FREE);
        }
        if (timer <= sf::seconds(-2) && stepTwo) {
            stepTwo = false;
            field.bCells.front()->setStatus(BCell::FREE);
        }
// ---

        for (int i = 0; i < CellType::COUNT; ++i) {
            switch (i) {
                case PATHOGEN:
                    drawing(field.pathogens, field, window, deltaTime);
                    break;
                case BODY:
                    newBodies.clear();
                    for (BodyCell *cell: field.bodies)
                        cell->cellDivision(deltaTime, newBodies);
                    field.bodies.insert(field.bodies.end(), newBodies.begin(), newBodies.end());
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

    sf::RenderWindow window(sf::VideoMode(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT), "Ecosystem",
                            sf::Style::Titlebar | sf::Style::Close);
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
