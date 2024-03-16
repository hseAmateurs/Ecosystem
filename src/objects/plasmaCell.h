//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_PLASMACELL_H
#define ECOSYSTEM_PLASMACELL_H


#include "cell.h"
#include "../utils/cells.h"

class PlasmaCell : public Cell {
public:
    explicit PlasmaCell(const Assets::CellParam &cellParam) :
            Cell(cellParam, texture::plasmaCell, color::PLASMA) { };

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;
};


#endif //ECOSYSTEM_NEUTROCELL_H
