//
// Created by Денис Громачихин on 19.02.2024.
//

#include "pathogenCell.h"
#include <iostream>

void PathogenCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}

void PathogenCell::update(Field &field, sf::Time deltaTime) {
    const int INF = 30000;

    sf::Vector2f closestBody;
    float minDistance = INF;
    sf::Vector2f hunterPos = getPosition();

    for (BodyCell *otherCell: field.bodies) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && distance < PATH_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }

        if (distance <= 3)
            if (!otherCell->texture.isAnimDying()) {
                otherCell->texture.startDying();
                otherCell->setKillerCode(getCode());
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
    if (texture.isDead()) kill();
    move(velocity * deltaTime.asSeconds());
}
