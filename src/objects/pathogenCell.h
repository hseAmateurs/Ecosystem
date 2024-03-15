#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H


#include "cell.h"
#include "../utils/cells.h"

class PathogenCell : public Cell {
public:
    explicit PathogenCell(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::pathogen, color::PATHOGEN) {
        setCode(rand() % 31 + '@');
    }

    virtual void runScript(Field &field, sf::Time deltaTime) override;
};

#endif //ECOSYSTEM_PATHOGENCELL_H
