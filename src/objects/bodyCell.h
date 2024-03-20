//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"
#include "../utils/cells.h"

class BodyCell : public Cell {
public:
    explicit BodyCell(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::bodyCell, color::BODY),
              lifeTime(sf::seconds(rand() % 20 + 15)) { }

    BodyCell(const BodyCell &right, const sf::Vector2f &newPos);

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;

private:
    void cellDivision(Field &field);

    sf::Time lifeTime;
    sf::Clock divisionTimer;
    sf::Time randomTime = sf::seconds(rand() % 20 + 15);
};


#endif //ECOSYSTEM_BODYCELL_H
