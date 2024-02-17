#include <SFML/Graphics.hpp>
#include "cell.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

int main() {
    // Простой пример для проверки работы

    std::vector<Cell> cells;
    std::vector<Cell> bodyCells;
    std::vector<Cell> macroCells;
    std::vector<Cell> neutroCells;

    std::vector<float> radiusArr;
    std::vector<int> sizeArr;
    std::vector<float> speedArr;
    std::vector<float> posXArr;
    std::vector<float> posYArr;


    


    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem");


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255,255,255));

        //Cell cell1(radius1, size1, speed1, sf::Color::Red, posX1, posY1);
        Cell cell2(30, 10, 30, sf::Color::Red, 300, 400);

        //cell1.setPosition(1000, 700);
        cell2.draw((window));


        window.display();
    }

    return 0;
}
