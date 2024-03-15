//
// Created by Денис Громачихин on 19.02.2024.
//

#include "pathogenCell.h"


void PathogenCell::runScript(Field &field, sf::Time deltaTime) {
    sf::Vector2f closestBody;
    float minDistance = INF;

    for (BodyCell *otherCell: field.bodies) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = getDistance(bodyPos, getPosition());
        if (distance < minDistance && distance < PATH_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }

        if (distance <= radius + otherCell->getRadius())
            otherCell->kill();
    }

    if (minDistance == INF)
        setRandomMovement();
    else {
        velocity = closestBody - getPosition();
        normalizeVelocity();
    }
    reflectionControl();
    updateCollision(field.pathogens);
    move(velocity * deltaTime.asSeconds());
}
