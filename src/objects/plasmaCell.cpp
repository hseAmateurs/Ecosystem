//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>

#include "plasmaCell.h"


PlasmaCell::PlasmaCell(const Assets::CellParam &cellParam) :
        Cell(cellParam, texture::plasmaCell, color::PLASMA),
        releasedAnti(0) {
    const int fieldRadius = BRAIN_RADIUS - 4 * Assets::instance().cellParams[CellType::BCELL].radius;
    float x, y;
    do {
        x = SCREEN_WIDTH - rand() % (2 * fieldRadius);
        y = SCREEN_HEIGHT - rand() % (2 * fieldRadius);
    } while (sqrt(pow(x - SCREEN_WIDTH, 2) + pow(y - SCREEN_HEIGHT, 2)) > fieldRadius
             || x > SCREEN_WIDTH || y > SCREEN_HEIGHT);

    setPosition(x, y);
}

void PlasmaCell::runScript(Field &field, const sf::Time &deltaTime) {
    setRandomMovement();
    plasmaReflectionControl();
    updateCollision(field.bCells);
    move(velocity * deltaTime.asSeconds());

    if (timer.getElapsedTime() < PLASMA_ANTI_DELAY) return;

    auto *newAntibody = new Antibody(Assets::instance().cellParams[CellType::ANTI]);
    newAntibody->setPosition(getPosition() + sf::Vector2f(1, 1));
    newAntibody->setCode(getCode());
    field.newAntis.push_back(newAntibody);

    releasedAnti++;
    timer.restart();
    if (releasedAnti == ANTI_COUNT) kill();
}

void PlasmaCell::plasmaReflectionControl() {
    const int fieldRadius = BRAIN_RADIUS - 4 * Assets::instance().cellParams[CellType::BCELL].radius;
    if (sqrt(pow(getPosition().x - SCREEN_WIDTH, 2) + pow(getPosition().y - SCREEN_HEIGHT, 2)) > fieldRadius
        || (getPosition().x + radius) > SCREEN_WIDTH || (getPosition().y + radius) > SCREEN_HEIGHT) {
        sf::Vector2f center(SCREEN_WIDTH - 0.5 * fieldRadius, SCREEN_HEIGHT - 0.5 * fieldRadius);
        velocity = center - getPosition();
        normalizeVelocity();
    }
}
