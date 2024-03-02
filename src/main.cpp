#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

#include "utils/initialization.h"
#include "textures/primaryCell.h"

using namespace utils;

bool isRun = true;

template<class T>
void drawing(vector<T> &cells, Field &field, sf::RenderWindow &window, sf::Time &deltaTime) {
    for (auto &cell: cells) {
        cell.update(field.pathogens, field.bodies, field.macroes, field.neutroes, deltaTime);
        window.draw(cell);
        cell.drawTexture(window);
    }
}

void renderingThread(sf::RenderWindow *window, Field *field) {
    window->setActive(true);
    sf::Clock clock;
//    texture::PrimaryCell primaryCell({400, 300}, 100, 100, sf::Color::Black);
//    texture::Neutrophil neutrophil({1200, 300}, 100);
//    texture::Macrophage macrophage({400, 600,}, 100);
//    texture::Antibody antibody({1200, 600}, 50);
//    texture::Pathogen pathogen({800, 450}, 100, 720);

    while (isRun) {
        window->clear(sf::Color(255, 255, 255));

//        primaryCell.update();
//        window.draw(primaryCell);

        sf::Time deltaTime = clock.restart();

        for (int i = 0; i < 4; ++i) {
            switch (i) {
                case PATHOGEN:
                    drawing(field->pathogens, *field, *window, deltaTime);
                    break;
                case BODY:
                    drawing(field->bodies, *field, *window, deltaTime);
                    break;
                case MACRO:
                    drawing(field->macroes, *field, *window, deltaTime);
                    break;
                case NEUTRO:
                    drawing(field->neutroes, *field, *window, deltaTime);
                    break;
                default:
                    std::cerr << "Undefined cell type\n";
            }
        }
        window->display();
    }
}

int main() {
    setbuf(stdout, nullptr);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    Field field = initField(readCSV("../data.csv"), window);

    // отключаем контекст окна после инициалазиции поля
    window.setActive(false);

    // запускаем поток
    sf::Thread thread(std::bind(&renderingThread, &window, &field));
    thread.launch();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRun = false;
                thread.wait();
                window.close();
            }
        }
    }

    return 0;
}
