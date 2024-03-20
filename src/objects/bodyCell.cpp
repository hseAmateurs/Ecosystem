//
// Created by Денис Громачихин on 19.02.2024.
//

#include "bodyCell.h"


void BodyCell::runScript(Field &field, const sf::Time &deltaTime) {
    cellDivision(field);
    setRandomMovement();
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}

void BodyCell::cellDivision(Field &field) {


    if (divisionTimer.getElapsedTime() >= randomTime) {
        float x1, y1;
        do {
            x1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            y1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            randomTime = sf::seconds(rand() % 20 + 15);
        } while (x1 == 0 && y1 == 0);

        field.newBodies.push_back(
                new BodyCell(*this, getPosition() + sf::Vector2f(x1, y1))
        );
        divisionTimer.restart();
    }
}
