//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>

#include "macroCell.h"

using namespace brain;


void MacroCell::runScript(Field &field, const sf::Time &deltaTime) {
    if (m_status == HUNTING) {
        hunting(field, deltaTime);
        return;
    }

    if (m_status == DELIVERY) {
        // Первая клетка свободна
        BCell::Status firstStatus = BCell::statuses[0];
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

    if ((m_status == CHECKING || m_status == SEARCH) && isBCellReady(field)) {
        auto &bCell = field.bCells[bCellIndex];
        BCell::statuses[bCellIndex] = BCell::BUSY;

        // Запуск анимированного подбора
        if (bCell->getCode() == ' ') {
            m_status = SEARCH;
            bCell->setCode(INIT_CODE);
            timer.restart();
            return;
        }
        if (bCell->getCode() == getCode()) {
            bCell->generatePulse();
            BCell::statuses[bCellIndex] = BCell::FREE;
            runPlasma(field);
            return;
        }
        if (m_status == SEARCH) {
            if (timer.getElapsedTime() < SEARCH_CODE_DELAY) return;
            bCell->setCode((char)(bCell->getCode() + 1));
            timer.restart();
            return;
        }
        if (bCellIndex + 1 == field.bCells.size()) {
            scrollBCells(field);
            return;
        }
        // Запуск анимации перемещения (нельзя переместиться на клетку с AWAIT, т.к. у неё уже есть пара)
        if (BCell::statuses[bCellIndex + 1] == BCell::FREE)
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

void MacroCell::runPlasma(Field &field) {
    bool isExist = false;
    for (PlasmaCell *plasma: field.plasmas) {
        // Если среди плазмы уже есть с нужным кодом, то сбрасываем её счётчик
        if (plasma->getCode() == getCode()) {
            plasma->resetReleasedAnti();
            isExist = true;
            break;
        }
    }
    if (!isExist) {
        // Иначе создаём новую (ограничения на кол-во работающей плазмы пока нет)
        auto *newPlasma = new PlasmaCell(Assets::instance().cellParams[CellType::PLASMA]);
        newPlasma->setCode(getCode());
        field.plasmas.push_back(newPlasma);
    }
    kill();
}

bool MacroCell::isBCellReady(const Field &field) const {
    for (BCell *cell: field.bCells) {
        if (cell->getStatus() == BCell::MOVING || cell->isDying())
            return false;
    }
    return true;
}

void MacroCell::moveNextPrepare(Field &field) {
    m_status = MOVING;
    std::cout << "Start moveNext (from " << bCellIndex << "): " << getCode() << "\n";
    BCell::statuses[bCellIndex + 1] = BCell::BUSY;
    BCell::statuses[bCellIndex] = BCell::FREE;
    bCellIndex++;
    sf::Vector2f nextPos = getXY(bCellIndex, field.bCells.size(), MACRO_DISTANCE);
    sf::Vector2f curPos = getXY(bCellIndex - 1, field.bCells.size(), MACRO_DISTANCE);
    anim = {
            atan2(SCREEN_HEIGHT - nextPos.y, SCREEN_WIDTH - nextPos.x),
            atan2(SCREEN_HEIGHT - curPos.y, SCREEN_WIDTH - curPos.x),
            600 + (double)(rand() % 1000 - 500),
            speed
    };
    timer.restart();
}

void MacroCell::scrollBCells(Field &field) {
    // Защита от одновременного смещения и B-клеток, и макрофагов по ним
    for (MacroCell *cell: field.macroes)
        if (cell->getStatus() == MOVING || cell->getStatus() == SEARCH)
            return;
    std::cout << "Run scroll: " << getCode() << "\n";

    auto newBCell = new BCell(Assets::instance().cellParams[CellType::BCELL]);
    newBCell->setPosition(getXY((int)field.bCells.size(), (int)field.bCells.size()));
    field.bCells.push_back(newBCell);

    // Простановка ожидаемых статусов, чтобы клетки,
    // которые находятся раньше в массиве, не сломали очередь следования в кругу
    int bCellAmount = field.bCells.size();
    for (int i = 0; i < bCellAmount; ++i)
        field.bCells[i]->scrollPrepare(i, bCellAmount);
}

void MacroCell::hunting(Field &field, const sf::Time &deltaTime) {
    sf::Vector2f closestBody;
    float minDistance = INF;

    for (PathogenCell *&otherCell: field.pathogens) {
        if (otherCell->isDying()) continue;
        sf::Vector2f bodyPos = otherCell->getPosition();
        float distance = getDistance(bodyPos, getPosition());
        if (distance < minDistance && distance < IMMUNE_HUNT_TRIGGER) {
            minDistance = distance;
            closestBody = bodyPos;
        }
        if (distance <= radius) {
            setCode(otherCell->getCode());
            m_status = DELIVERY;
            otherCell->kill();
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
    updateCollision(field.macroes);
    updateCollision(field.bodies);
    move(velocity * deltaTime.asSeconds());
}
