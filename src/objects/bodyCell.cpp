//
// Created by Денис Громачихин on 19.02.2024.
//

#include "bodyCell.h"
#include <iostream>
#include <ctime>

void BodyCell::drawTexture(sf::RenderWindow &window) {
    sf::Vector2f radiusOffset(getRadius(), getRadius());
    texture.changeCenter(getPosition() + radiusOffset);
    texture.update();
    window.draw(texture);
}

void BodyCell::cellDivision(sf::Time &deltaTime, std::vector<BodyCell> &bodyCells)
{
    lifeTime += deltaTime;
    //srand(time(0));
    sf::Time randomTime = sf::seconds(rand() % 20 + 15);

    if (lifeTime.asSeconds() >= randomTime.asSeconds())
    {
            BodyCell newCell(radius, size, speed, center, color);

        float x1, y1;
        do {
            x1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            y1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        } while (x1 == 0 && y1 == 0);


        newCell.setPosition((getPosition() + sf::Vector2f(x1, y1)));
            bodyCells.push_back(newCell);
            //std::cout<<"hui"<<"\n";
            lifeTime = sf::Time::Zero;

    }
}
