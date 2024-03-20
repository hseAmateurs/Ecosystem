//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>

#include "bCell.h"

using namespace brain;

std::vector<BCell::Status> BCell::statuses;

void BCell::runScript(Field &field, const sf::Time &deltaTime) {
    if (m_status != MOVING) return;

    updateAngle(anim, timer);
    if (std::abs(anim.targetAngle - anim.currentAngle) <= angleEps) {
        if (m_index == 0) kill();
        m_status = AWAIT;
        anim.currentAngle = anim.targetAngle;
    }
    setPosition(getXY(anim.currentAngle));
}

void BCell::scrollPrepare(const int index, const int amount) {
    m_index = index;
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
