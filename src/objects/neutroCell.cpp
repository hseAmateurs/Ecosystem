//
// Created by Денис Громачихин on 19.02.2024.
//

#include "neutroCell.h"


void NeutroCell::runScript(Field &field, sf::Time deltaTime) {
    sf::Vector2f closestBody;
    float minDistance = INF;

    for (PathogenCell *&otherCell: field.pathogens) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = getDistance(bodyPos, getPosition());
        if (distance < minDistance && distance < IMMUNE_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }
        if (distance <= radius + otherCell->getRadius() && !otherCell->isDying()) {
            size -= otherCell->getSize();
            if (size <= 0) kill();
            otherCell->kill();
        }
    }

    if (minDistance == INF)
        setRandomMovement();
    else {
        velocity = closestBody - getPosition();
        normalizeVelocity();
    }
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
