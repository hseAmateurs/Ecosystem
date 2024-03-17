//
// Created by Денис Громачихин on 19.02.2024.
//

#include "pathogenCell.h"


void PathogenCell::runScript(Field &field, const sf::Time &deltaTime) {
    sf::Vector2f closestBody;
    float minDistance = INF;

    for (BodyCell *otherCell: field.bodies) {
        if(otherCell->isDying()) continue;
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = getDistance(bodyPos, getPosition());
        if (!otherCell->isDying() && distance < minDistance && distance < PATH_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }

        if (distance <= radius + otherCell->getRadius()) {
            field.newPathogens.push_back(
                    new PathogenCell(*this, bodyPos)
            );
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
    updateCollision(field.pathogens);
    move(velocity * deltaTime.asSeconds());
}
