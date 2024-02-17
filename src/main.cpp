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


    std::ifstream file("data.csv");
    std::string line;
    std::vector<float> radii;
    std::vector<int> sizes;
    std::vector<float> speeds;
    std::vector<sf::Color> colors;
    std::vector<float> posXs;
    std::vector<float> posYs;
    std::vector<int> counts;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        float radius = std::stof(token);
        radii.push_back(radius);

        std::getline(ss, token, ',');
        int size = std::stoi(token);
        sizes.push_back(size);

        std::getline(ss, token, ',');
        float speed = std::stof(token);
        speeds.push_back(speed);

        std::getline(ss, token, ',');
        int r, g, b, a;
        std::stringstream(token) >> std::hex >> r;
        std::getline(ss, token, ',');
        std::stringstream(token) >> std::hex >> g;
        std::getline(ss, token, ',');
        std::stringstream(token) >> std::hex >> b;
        std::getline(ss, token, ',');
        std::stringstream(token) >> std::hex >> a;
        sf::Color color(r, g, b, a);
        colors.push_back(color);

        std::getline(ss, token, ',');
        float posX = std::stof(token);
        posXs.push_back(posX);

        std::getline(ss, token, ',');
        float posY = std::stof(token);
        posYs.push_back(posY);

        std::getline(ss, token, ',');
        int count = std::stoi(token);
        counts.push_back(count);
    }









    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem");


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255,255,255));

        //Cell cell1(radii.at(0), sizes.at(0), speeds.at(0), colors.at(0), posXs.at(0), posYs.at(0));

        //cell1.setPosition(1000, 700);
        //cell1.draw(window);


        window.display();
    }

    return 0;
}
