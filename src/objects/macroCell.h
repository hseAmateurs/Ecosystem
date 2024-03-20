//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_MACROCELL_H
#define ECOSYSTEM_MACROCELL_H


#include "cell.h"
#include "../utils/cells.h"

#include "../utils/brain.h"

#include <iostream>

class MacroCell : public Cell {
public:
    enum Status {
        HUNTING,
        DELIVERY,
        CHECKING,
        MOVING,
        SEARCH
    };

    MacroCell(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::macrophage, color::MACRO),
              m_status(HUNTING), bCellIndex(0) { }

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;

    Status getStatus() const { return m_status; }

private:
    void runPlasma(Field &field);

    void scrollBCells(Field &field);

    void hunting(Field &field, const sf::Time &deltaTime);

    void moveNextPrepare(Field &field);

    bool isBCellReady(const Field &field) const;

    Status m_status;
    int bCellIndex;

    brain::Animation anim;
};

#endif //ECOSYSTEM_MACROCELL_H
