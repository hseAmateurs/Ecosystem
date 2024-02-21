#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H


#include "cell.h"

class PathogenCell : public Cell {
public:
    PathogenCell(float radius, int size, float speed, const sf::Color &color, float posX, float posY)
            : Cell(radius,
                   size, speed,
                   color, posX,
                   posY) { }
};


#endif //ECOSYSTEM_PATHOGENCELL_H
