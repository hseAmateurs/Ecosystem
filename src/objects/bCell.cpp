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
    if (m_status == SCROLL) {
        scrollPrepare(field);
        return;
    }
    if (m_status == MOVING) {
        updateAngle(anim, timer);
        setPosition(getXY(anim.currentAngle));
        if (anim.currentAngle >= anim.targetAngle) {
            int index = getID(field);
            if(index == 0) {
                field.bCells.erase(field.bCells.begin());
                delete this;
            }
            m_status = FREE;
        }
        return;
    }
}

void BCell::scrollPrepare(const Field &field) {
    int index = getID(field);
    sf::Vector2f nextPos = getXY(index - 1, field.bCells.size() - 1);
    sf::Vector2f curPos = getXY(index, field.bCells.size() - 1);
    anim = {
            atan2(SCREEN_HEIGHT - nextPos.y, SCREEN_WIDTH - nextPos.x),
            atan2(SCREEN_HEIGHT - curPos.y, SCREEN_WIDTH - curPos.x),
            600 + (double)(rand() % 1000 - 500),
            speed
    };
    m_status = MOVING;
    timer.restart();
}

int BCell::getID(const Field &field) const {
    int index = 0;
    for (const BCell *cell: field.bCells) {
        if (cell == this) return index;
        index++;
    }
}
