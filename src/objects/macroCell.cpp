//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>
#include "macroCell.h"

using namespace brain;

void MacroCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}

void MacroCell::runPlasma(Field &field) {
    kill();
    // run plasma
    // current delete cell
}

void MacroCell::update(Field &field, sf::Time deltaTime) {
    if (m_status == HUNTING) {
        hunting(field, deltaTime);
        return;
    }
    if (m_status == DELIVERY) {
        // Первая клетка свободна
        BCell::Status firstStatus = field.bCells.front()->getStatus();
        if (firstStatus == BCell::FREE) {
            const sf::Vector2f targetPos = getXY(bCellIndex, field.bCells.size(), MACRO_DISTANCE);
            velocity = targetPos - getPosition();
            if (velocity.x < 1 && velocity.y < 1) {
                setPosition(targetPos);
                m_status = CHECKING;
                return;
            }
            normalizeVelocity();
        }
        else
            setRandomMovement();

        reflectionControl();
        move(velocity * deltaTime.asSeconds());
        return;
    }
    if (m_status == CHECKING && isBCellReady(field)) {
        auto &bCell = field.bCells[bCellIndex];
        bCell->setStatus(BCell::BUSY);

        // Добавить задержку для чекинга (можно анимировать радиус ещё)
        if (!bCell->getCode()) {
            bCell->setCode(getCode()); // Вместо set будет анимированный подбор
            bCell->setStatus(BCell::FREE);
            runPlasma(field);
            return;
        }
        if (bCell->getCode() == getCode()) {
            bCell->setStatus(BCell::FREE);
            runPlasma(field);
            return;
        }
        if (bCellIndex + 1 == field.bCells.size()) {
            scrollBCells(field);
            return;
        }
        // Заупск анимации перемещения (нельзя переместиться на клетку с AWAIT, т.к. у неё уже есть пара)
        if (field.bCells[bCellIndex + 1]->getStatus() == BCell::FREE)
            moveNextPrepare(field);
        return;
    }

    if (m_status == MOVING) {
        updateAngle(anim, timer);
        if (std::abs(anim.targetAngle - anim.currentAngle) <= angleEps) {
            m_status = CHECKING;
            anim.currentAngle = anim.targetAngle;
        }
        setPosition(getXY(anim.currentAngle, MACRO_DISTANCE));
        return;
    }
}

bool MacroCell::isBCellReady(const Field &field) const {
    for (BCell *cell: field.bCells) {
        if (cell->getStatus() == BCell::MOVING)
            return false;
    }
    return true;
}

void MacroCell::moveNextPrepare(Field &field) {
    m_status = MOVING;
    std::cout << "Start moveNext (from " << bCellIndex << "): " << getCode() << "\n";
    field.bCells[bCellIndex + 1]->setStatus(BCell::BUSY);
    field.bCells[bCellIndex]->setStatus(BCell::FREE);
    bCellIndex++;
    sf::Vector2f nextPos = getXY(bCellIndex, field.bCells.size(), MACRO_DISTANCE);
    sf::Vector2f curPos = getXY(bCellIndex - 1, field.bCells.size(), MACRO_DISTANCE);
    anim = {
            atan2(SCREEN_HEIGHT - nextPos.y, SCREEN_WIDTH - nextPos.x),
            atan2(SCREEN_HEIGHT - curPos.y, SCREEN_WIDTH - curPos.x),
            600 + (double)(rand() % 1000 - 500),
            speed / 10
    };
    timer.restart();
}

void MacroCell::scrollBCells(Field &field) {
    // Защита от одновременного смещения и B-клеток, и макрофагов по ним
    for (MacroCell *&cell: field.macroes)
        if (cell->getStatus() == MOVING)
            return;
    std::cout << "Run scroll: " << getCode() << "\n";
    auto firstBCell = field.bCells.front();
    auto *newBCell = new BCell(*firstBCell);
    newBCell->setPosition(getXY((int)field.bCells.size(), (int)field.bCells.size()));
    field.bCells.push_back(newBCell);

    // Простановка ожидаемых статусов, чтобы клетки,
    // которые находятся раньше в массиве, не сломали очередь следования в кругу
    int bCellAmount = field.bCells.size();
    std::vector<BCell::Status> nextStatuses(bCellAmount);
    nextStatuses[0] = BCell::BUSY;
    for (int i = 1; i < bCellAmount; ++i) {
        BCell::Status nextStatus = field.bCells[i - 1]->getStatus();
        if (nextStatus == BCell::BUSY) nextStatus = BCell::AWAIT;
        nextStatuses[i] = nextStatus;
    }
    for (int i = 0; i < bCellAmount; ++i)
        field.bCells[i]->scrollPrepare(i, bCellAmount, nextStatuses[i]);
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
