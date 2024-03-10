//
// Created by Денис Громачихин on 19.02.2024.
//

#include "neutroCell.h"

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

    for (PathogenCell* &otherCell: field.pathogens) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && distance < HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }
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
        normalizeVelocity();
    }
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.pathogens);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
