//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>

#include "plasmaCell.h"


void PlasmaCell::runScript(Field &field, const sf::Time &deltaTime) {
    if (timer.getElapsedTime() < PLASMA_ANTI_DELAY) return;

    auto *newAntibody = new Antibody(Assets::instance().cellParams[CellType::ANTI]);
    newAntibody->setPosition(getPosition());
    newAntibody->setCode(getCode());
    field.newAntis.push_back(newAntibody);

    releasedAnti++;
    timer.restart();
    if(releasedAnti == ANTI_COUNT) kill();
}
