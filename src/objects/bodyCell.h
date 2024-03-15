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
              lifeTime(sf::seconds(-(rand() % 20 + 15))) { }

    BodyCell(const BodyCell &right, const sf::Vector2f &newPos) :
            Cell(right), lifeTime(sf::seconds(-(rand() % 20 + 15))) {
        setPosition(newPos);
    }

    virtual void runScript(Field &field, sf::Time deltaTime) override;

    void cellDivision(sf::Time &deltaTime, std::vector<BodyCell *> &bodyCells);

private:
    sf::Time lifeTime;
};


#endif //ECOSYSTEM_BODYCELL_H
