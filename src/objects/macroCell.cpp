//
// Created by Денис Громачихин on 19.02.2024.
//

#include "macroCell.h"

void MacroCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}

void MacroCell::update(Field &field, sf::Time deltaTime) {
    const int INF = 30000;

    sf::Vector2f closestBody;
    float minDistance = INF;
    int i = 0;
    int deadInd = -1;
    sf::Vector2f hunterPos = getPosition();

    for (PathogenCell *&otherCell: field.pathogens) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && distance < IMMUNE_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }
        if (distance <= radius) {
            if (!otherCell->texture.isAnimDying()){
                // this->setCode(otherCell->getCode());
                otherCell->setCode(' ');
                otherCell->texture.startDying();
            }
            if (otherCell->texture.isDead()){
                deadInd = i;
                delete field.pathogens.at(deadInd);
                field.pathogens.erase(field.pathogens.begin() + deadInd);
            }
        }
        i++;
    }

    if (minDistance == INF) {
        if (timer.getElapsedTime() > randomMoveInterval) {
            setRandomVelocity();
            auto randomSeconds = static_cast<float>(std::rand() % 5 + 1); // Случайное число от 1 до 5
            randomMoveInterval = sf::seconds(randomSeconds);
            timer.restart();
        }
    }
    else {
        velocity = closestBody - getPosition();
        velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
    }
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
