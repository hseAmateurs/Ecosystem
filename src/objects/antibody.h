#ifndef ECOSYSTEM_ANTIBODY_H
#define ECOSYSTEM_ANTIBODY_H

#include "cell.h"
#include "../utils/cells.h"

class Antibody : public Cell {
public:
    Antibody(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::antibody, color::ANTI),
              deathClock(sf::seconds(static_cast<float>(rand() % 5 + 2))) {
        setCode((char)(rand() % 31 + '@'));
    }

    virtual void runScript(Field &field, sf::Time deltaTime) override;

private:
    sf::Time deathClock;
    sf::Clock deathTimer;
};

#endif //ECOSYSTEM_ANTIBODY_H
