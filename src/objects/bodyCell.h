//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"
#include "../textures/primaryCell.h"

class BodyCell : public Cell {
public:
    BodyCell(float radius, int size, float speed, float posX, float posY)
            : Cell(radius, size,
                   speed,
                   posX, posY){ }

    void drawTexture(sf::RenderWindow& window);

private:
    texture::PrimaryCell texture;
};


#endif //ECOSYSTEM_BODYCELL_H
