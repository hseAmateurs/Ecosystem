//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"

class BodyCell : public Cell
{
public:
    BodyCell(float radius, int size, float speed, const sf::Color& color, float posX, float posY): Cell(radius, size, speed, color, posX, posY) {}
};


#endif //ECOSYSTEM_BODYCELL_H
