#ifndef ECOSYSTEM_ANTIBODY_H
#define ECOSYSTEM_ANTIBODY_H

#include "cell.h"
#include "../utils/cells.h"

class Antibody : public Cell {
public:
    Antibody(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::antibody, color::ANTI) { }

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;
};

#endif //ECOSYSTEM_ANTIBODY_H
