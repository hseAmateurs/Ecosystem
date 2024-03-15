//
// Created by Денис Громачихин on 19.02.2024.
//

#include "bodyCell.h"


void BodyCell::runScript(Field &field, sf::Time deltaTime) {
    setRandomMovement();
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}

void BodyCell::cellDivision(sf::Time &deltaTime, std::vector<BodyCell *> &bodyCells) {
    lifeTime += deltaTime;
    sf::Time randomTime = sf::seconds(rand() % 20 + 15);

    if (lifeTime.asSeconds() >= randomTime.asSeconds()) {
        float x1, y1;
        do {
            x1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            y1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        } while (x1 == 0 && y1 == 0);

        bodyCells.push_back(
                new BodyCell(*this, getPosition() + sf::Vector2f(x1, y1))
        );
        lifeTime = sf::Time::Zero;
    }
}
