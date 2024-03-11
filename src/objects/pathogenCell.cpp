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
    int i = 0;
    int deadInd = -1;
    sf::Vector2f newPos(-1000.f, -1000.f);

    for (BodyCell* otherCell: field.bodies) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && distance < PATH_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }

        if (distance <= radius+otherCell->getRadius()) {
            if (!otherCell->texture.isAnimDying()) {
                otherCell->texture.startDying();
            }

            if (otherCell->texture.isDead()){
                deadInd = i;
                newPos = otherCell->getPosition();
                PathogenCell *newCell = new PathogenCell(texture::pathogen, radius, size, speed, center,  color);
                newCell->setPosition(newPos);
                field.pathogens.push_back(newCell);
                break;
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
    updateCollision(field.pathogens);
    move(velocity * deltaTime.asSeconds());


}
