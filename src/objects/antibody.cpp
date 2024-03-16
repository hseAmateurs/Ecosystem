#include "antibody.h"

void Antibody::runScript(Field &field, const sf::Time &deltaTime) {
    sf::Vector2f closestBody;
    float minDistance = INF;
    bool foundPathogen = false;

    for (PathogenCell *&otherCell: field.pathogens) {
        if(otherCell->isDying()) continue;
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = getDistance(bodyPos, getPosition());
        if (distance < minDistance && otherCell->getCode() == getCode()) {
            minDistance = distance;
            closestBody = bodyPos;
            foundPathogen = true;
        }
        if (distance <= radius + otherCell->getRadius() && otherCell->getCode() == getCode()) {
            otherCell->kill();
            kill();
        }
    }

    if (foundPathogen) {
        deathTimer.restart();
        velocity = closestBody - getPosition();
        normalizeVelocity();
    }
    else {
        setRandomMovement();
        if (deathTimer.getElapsedTime() >= deathClock)
            kill();
    }
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.antis);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
