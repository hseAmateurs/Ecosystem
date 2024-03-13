#include "antibody.h"
#include <iostream>

void Antibody::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);
    code.setPosition(getPosition());
    window.draw(code);
}

void Antibody::antibodyDeath() {
    if(!this->texture.isAnimDying()){
        this->setCode(' ');
        this->texture.startDying();
    }
}

void Antibody::update(Field &field, sf::Time deltaTime) {
    const int INF = 30000;

    sf::Vector2f closestBody;
    float minDistance = INF;
    sf::Vector2f hunterPos = getPosition();
    bool foundPathogen = false;
    for (PathogenCell *&otherCell: field.pathogens) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && otherCell->getCode()==this->getCode()) {
            minDistance = distance;
            closestBody = bodyPos;
            foundPathogen = true;
        }
        if (distance <= radius + otherCell->getRadius() && otherCell->getCode()==this->getCode()) {
            if (!otherCell->texture.isAnimDying()) {
                otherCell->setCode(' ');
                otherCell->texture.startDying();
            }
            antibodyDeath();
        }
    }

    if (foundPathogen){
        deathTimer.restart();
        velocity = closestBody - getPosition();
        normalizeVelocity();
    }
    else {
        setRandomMovement();
        if(deathTimer.getElapsedTime()>=deathClock){
            antibodyDeath();
        }
    }
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.antis);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    if (texture.isDead()) kill();
    move(velocity * deltaTime.asSeconds());
}

