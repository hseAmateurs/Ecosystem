//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>
#include "macroCell.h"

void MacroCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}

void MacroCell::update(Field &field, sf::Time deltaTime) {
    if (m_status == HUNTING) {
        hunting(field, deltaTime);
        return;
    }
    if (m_status == DELIVERY) {
        if (field.bCells.front()->getStatus() != BCell::FREE) {
            setRandomMovement();
            move(velocity * deltaTime.asSeconds());
            return;
        }

        const sf::Vector2f targetPos = BCell::nextOrbitXY(bCellIndex, field.bCells.size());
        velocity = targetPos - getPosition();

        if(velocity.x < 1 && velocity.y < 1) {
            setPosition(targetPos);
            m_status = CHECKING;
        }

        normalizeVelocity();

        reflectionControl();
        move(velocity * deltaTime.asSeconds());
    }
    if(m_status == CHECKING) {
        auto &bCell = field.bCells[bCellIndex];
        bCell->setStatus(BCell::BUSY);
        if(!bCell->getCode()) bCell->setCode(getCode());
        m_status = DELIVERY;
        // Проверять и двигать клетку
        // Возможно стоит фукнции из bCell вынести в общий файл, т.к. они повторяются
        return;
    }
}

void MacroCell::scrollBCells(Field &field) {
    // Защита от одновременного смещения и B-клеток, и макрофагов по ним
    for (BCell *&cell: field.bCells)
        if (cell->getStatus() == BCell::BUSY || cell->getStatus() == BCell::MOVING)
            return;

    auto firstBCell = field.bCells.front();
    auto *newBCell = new BCell(texture::bCell,
                               firstBCell->getRadius(),
                               firstBCell->getSize(),
                               firstBCell->getSpeed(),
                               BCell::getXY((int)field.bCells.size(), (int)field.bCells.size()),
                               firstBCell->getColor());
    field.bCells.push_back(newBCell);

    for (BCell *&cell: field.bCells)
        cell->setStatus(BCell::SCROLL);

//    delete field.bCells.front();
//    field.bCells.erase(field.bCells.begin());
}

void MacroCell::hunting(Field &field, sf::Time deltaTime) {
    const int INF = 30000;

    sf::Vector2f closestBody;
    float minDistance = INF;
    sf::Vector2f hunterPos = getPosition();

    for (PathogenCell *&otherCell: field.pathogens) {
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                   (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
        if (distance < minDistance && distance < HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
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
    updateCollision(field.pathogens);
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
