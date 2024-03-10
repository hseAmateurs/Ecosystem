//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>
#include "bCell.h"

void BCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);
}

BCell::~BCell() {
    std::cout << "Deleted\n";
}

void BCell::updateAngle() {
    double deltaAngle = anim.targetAngle - anim.currentAngle;
    double scale = sin(M_PI * timer.getElapsedTime().asSeconds() / (anim.speedScale / speed));
    anim.currentAngle += deltaAngle * scale;
    if(anim.currentAngle > anim.targetAngle) anim.currentAngle = anim.targetAngle;
}


void BCell::update(Field &field, sf::Time deltaTime) {
    if (m_status == MOVE) {
        int index = getID(field);
        sf::Vector2f nextPos = getXY(index + 1, field.bCells.size());
        sf::Vector2f pos = getXY(index, field.bCells.size());
        anim = {
                atan2(SCREEN_HEIGHT - nextPos.y, SCREEN_WIDTH - nextPos.x),
                atan2(SCREEN_HEIGHT - pos.y, SCREEN_WIDTH - pos.x),
                600 + (double)(rand() % 1000 - 500)
        };
        m_status = SCROLLING;
        timer.restart();
        return;
    }
    if(m_status == SCROLLING) {
        updateAngle();
        setPosition(getXY(anim.currentAngle));
        if(anim.currentAngle >= anim.targetAngle) {
            m_status = FREE;
        }
        return;
    }
}

int BCell::getID(const Field &field) const {
    int index = 0;
    for (const BCell *cell: field.bCells) {
        if (cell == this) return index;
        index++;
    }
}


sf::Vector2f BCell::getXY(double angle) {
    float posX = std::cos(angle) * (BCELL_DISTANCE * BRAIN_RADIUS);
    float posY = std::sin(angle) * (BCELL_DISTANCE * BRAIN_RADIUS);
    return {SCREEN_WIDTH - posX, SCREEN_HEIGHT - posY};
}

sf::Vector2f BCell::getXY(const int index, const int amount) {
    const double angleOffset = M_PI / 8;
    double angle = (M_PI / 2 + angleOffset) / (amount + 1) * (index + 1) - angleOffset / 2;
    return getXY(angle);
}
