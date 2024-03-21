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
            Cell(cellParam, texture::plasmaCell, color::PLASMA),
            releasedAnti(0) { spawnPlasmaCell(); };

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;

    void resetReleasedAnti() { releasedAnti = 0; }

private:
    int releasedAnti;
    sf::Clock plasmaTimer;

    void spawnPlasmaCell();
    void plasmaReflectionControl();
};


#endif //ECOSYSTEM_NEUTROCELL_H
