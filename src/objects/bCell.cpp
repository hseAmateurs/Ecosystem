//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>

#include "bCell.h"

using namespace brain;

BCell::BCell(const BCell &right, const sf::Vector2f &newPos) :
        Cell(right), m_status(FREE) {
    setCode(' ');
    setPosition(newPos);
}

void BCell::runScript(Field &field, const sf::Time &deltaTime) {
    if (m_status != MOVING) return;

    updateAngle(anim, timer);
    if (std::abs(anim.targetAngle - anim.currentAngle) <= angleEps) {
        if (m_index == 0) kill();
        m_status = m_nextStatus;
        anim.currentAngle = anim.targetAngle;
    }
    setPosition(getXY(anim.currentAngle));
}

void BCell::scrollPrepare(const int index, const int amount, Status nextStatus) {
    m_index = index;
    m_nextStatus = nextStatus;
    sf::Vector2f nextPos = getXY(m_index - 1, amount - 1);
    sf::Vector2f curPos = getXY(m_index, amount - 1);
    anim = {
            atan2(SCREEN_HEIGHT - nextPos.y, SCREEN_WIDTH - nextPos.x),
            atan2(SCREEN_HEIGHT - curPos.y, SCREEN_WIDTH - curPos.x),
            600 + (double)(rand() % 1000 - 500),
            speed
    };
    m_status = MOVING;
    timer.restart();
}
