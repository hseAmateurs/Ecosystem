#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "utils/initialization.h"
//#include "utils/drawing.h"


template<class T>
void drawing(const vector<T> &cells, sf::RenderWindow &window) {
    for (auto cell : cells) {
        cell.draw(window);
    }
}

using namespace utils;

int main() {
    setbuf(stdout, nullptr);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

//    texture::PrimaryCell primaryCell({400, 300}, 100);
//    texture::Neutrophil neutrophil({1200, 300}, 100);
//    texture::Macrophage macrophage({400, 600,}, 100);
//    texture::Antibody antibody({1200, 600}, 50);
//    texture::Pathogen pathogen({800, 450}, 100, 720);

    sf::Clock clock;
    Field field = initField(readCSV("../data.csv"), window);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();
        window.clear(sf::Color(255,255,255));

        for (int i = 0; i < 4; ++i) {
            switch (i) {
                case PATHOGEN:
                    drawing(field.pathogens, window);
                    break;
                case BODY:
                    drawing(field.bodies, window);
                    break;
                case MACRO:
                    drawing(field.macroes, window);
                    break;
                case NEUTRO:
                    drawing(field.neutroes, window);
                    break;
                default:
                    std::cerr << "Undefined cell type\n";
            }
        }

        window.display();
    }

    return 0;
}
