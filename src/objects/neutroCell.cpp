//
// Created by Денис Громачихин on 19.02.2024.
//

#include "neutroCell.h"
#include <iostream>

void NeutroCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);
}

void NeutroCell::update(Field &field, sf::Time deltaTime) {
    const int INF = 30000;

    sf::Vector2f closestBody;
    float minDistance = INF;
    sf::Vector2f hunterPos = getPosition();

    for (PathogenCell *&otherCell: field.pathogens) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && distance < IMMUNE_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }
        if (distance <= radius + otherCell->getRadius()) {
            if (!otherCell->texture.isAnimDying()) {
                this->size = this->size - otherCell->getSize();
                if (this->size <= 0 && !this->texture.isAnimDying()) {
                    this->texture.startDying();
                }
                otherCell->setCode(' ');
                otherCell->texture.startDying();
                texture.changeRadius(radius+7);
            }
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
    if (texture.isDead()) kill();
    move(velocity * deltaTime.asSeconds());
}
