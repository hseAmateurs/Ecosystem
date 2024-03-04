#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>


#include "utils/initialization.h"
#include "textures/primaryCell.h"

using namespace utils;

bool isRun = true;

template<class T>
void drawing(vector<T> &cells, Field &field, sf::RenderWindow &window, sf::Time &deltaTime) {
    for (auto &cell: cells) {
        if(cell.getName()!='b')
            cell.updateHunters(field.pathogens,field.bodies, field.macroes, field.neutroes, deltaTime);
        else
            cell.updateBody(field.pathogens,field.bodies, field.macroes, field.neutroes, deltaTime);
        window.draw(cell);
        cell.drawTexture(window);
    }
}

void renderingThread(sf::RenderWindow &window, Field &field) {
    window.setActive(true);
    sf::Clock clock;


    while (isRun) {
        window.clear(sf::Color(255, 255, 255));
        sf::Time deltaTime = clock.restart();

        for (int i = 0; i < 4; ++i) {

            switch (i) {
                case PATHOGEN:
                    drawing(field.pathogens, field, window, deltaTime);
                    break;
                case BODY:
                    for (BodyCell &cell : field.bodies)
                        cell.cellDivision(deltaTime, field.bodies);
                    drawing(field.bodies, field, window, deltaTime);
                    break;
                case MACRO:
                    drawing(field.macroes, field, window, deltaTime);
                    break;
                case NEUTRO:
                    drawing(field.neutroes, field, window, deltaTime);
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
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    Field field = initField(readCSV("../data.csv"), window);

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

    return 0;
}
