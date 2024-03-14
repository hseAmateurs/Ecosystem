//
// Created by Денис Громачихин on 19.02.2024.
//

#include "bodyCell.h"

void BodyCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);
}

void BodyCell::cellDivision(sf::Time &deltaTime, std::vector<BodyCell *> &bodyCells) {
    lifeTime += deltaTime;
    sf::Time randomTime = sf::seconds(rand() % 20 + 15);

    if (lifeTime.asSeconds() >= randomTime.asSeconds()) {
        auto *newCell = new BodyCell(*this);

        float x1, y1;
        do {
            x1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            y1 = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        } while (x1 == 0 && y1 == 0);

        newCell->setPosition((getPosition() + sf::Vector2f(x1, y1)));
        bodyCells.push_back(newCell);
        lifeTime = sf::Time::Zero;
    }
}

void BodyCell::update(Field &field, sf::Time deltaTime) {
    if (texture.isDead()) kill();
    setRandomMovement();
    reflectionControl();
    updateCollision(field.neutroes);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}

void BodyCell::createPathogen(PathogenCell *pathogen, std::vector<PathogenCell *> &newPathogens) {
    if (texture.isAnimDying() && killerCode) {
        auto *newPathogen = new PathogenCell(*pathogen);
        newPathogen->setPosition(getPosition());
        newPathogen->setCode(getKillerCode());
        killerCode = 0;
        std::cout << "Create pathogen\n";
        newPathogen->texture.startBirthing();
        newPathogens.push_back(newPathogen);
    }
}
