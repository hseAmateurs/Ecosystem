
#ifndef ECOSYSTEM_HUNTERCELL_H
#define ECOSYSTEM_HUNTERCELL_H


#include "cell.h"

class HunterCell: public Cell {
public:
    HunterCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : Cell(radius, size,
                   speed,
                   center, color) {}

};


#endif //ECOSYSTEM_HUNTERCELL_H
