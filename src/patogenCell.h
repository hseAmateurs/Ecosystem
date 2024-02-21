#include "cell.h"

#ifndef ECOSYSTEM_PATOGENCELL_H
#define ECOSYSTEM_PATOGENCELL_H


class PatogenCell : public Cell
{
public:
    PatogenCell(float radius, int size, float speed, const sf::Color& color, float posX, float posY): Cell(radius, size, speed, color, posX, posY) {}
};


#endif //ECOSYSTEM_PATOGENCELL_H
