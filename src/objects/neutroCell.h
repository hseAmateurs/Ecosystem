//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "cell.h"

class NeutroCell : public Cell {
public:
    NeutroCell(float radius, int size, float speed, const sf::Color &color, float posX, float posY) :
            Cell(radius, size,
                 speed, color,
                 posX,
                 posY) { }
};


#endif //ECOSYSTEM_NEUTROCELL_H
