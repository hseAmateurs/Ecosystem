#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../core/field.h"

class PathogenCell : public Cell {
public:
    explicit PathogenCell(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::pathogen, color::PATHOGEN) {
        setCode((char)('!' + rand()%(Field::getDifficult()-'!'+1)));
    }

    PathogenCell(const PathogenCell &right, const sf::Vector2f &newPos) :
            Cell(right) {
        setPosition(newPos);
    }

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;
};

#endif //ECOSYSTEM_PATHOGENCELL_H
