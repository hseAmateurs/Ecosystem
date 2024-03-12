//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>
#include "bCell.h"

using namespace brain;

void BCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}

BCell::~BCell() {
    std::cout << "Deleted\n";
}

void BCell::update(Field &field, sf::Time deltaTime) {
    if (m_status == MOVING) {
        updateAngle(anim, timer);
        if (std::abs(anim.targetAngle - anim.currentAngle) <= angleEps) {
            if (m_index == 0)
                kill();
            m_status = m_nextStatus;
            anim.currentAngle = anim.targetAngle;
        }
        setPosition(getXY(anim.currentAngle));
        return;
    }
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

BCell::~BCell() {
    std::cout << "Deleted\n";
}
