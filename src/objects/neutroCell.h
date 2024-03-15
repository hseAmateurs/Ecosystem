//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "cell.h"
#include "../utils/cells.h"

class NeutroCell : public Cell {
public:
    explicit NeutroCell(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::neutrophil, color::NEUTRO) { }

    virtual void runScript(Field &field, sf::Time deltaTime) override;
};

#endif //ECOSYSTEM_NEUTROCELL_H
