//
// Created by Денис Громачихин on 19.02.2024.
//

#include "pathogenCell.h"

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
    closestBody.x = 0;
    closestBody.y = 0;
    float minDistance = INF;
    sf::Vector2f hunterPos = getPosition();

    if (this->type() == CellType::PATHOGEN) {
        for (BodyCell* otherCell: field.bodies) {
            sf::Vector2f bodyPos = otherCell->getPosition();
            float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                       (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
            if (distance < minDistance && distance < HUNT_TRIGGER) {
                minDistance = distance;
                closestBody = bodyPos;
            }
        }
    }
    else if (this->type() == CellType::MACRO || this->type() == CellType::NEUTRO) {
        for (PathogenCell* &otherCell: field.pathogens) {
            sf::Vector2f bodyPos = otherCell->getPosition();
            float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                       (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
            if (distance < minDistance && distance < HUNT_TRIGGER) {
                minDistance = distance;
                closestBody = bodyPos;
            }
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
        velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
    }
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.pathogens);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
