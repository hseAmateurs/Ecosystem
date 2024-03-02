//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"
#include "../textures/primaryCell.h"

class BodyCell : public Cell {
public:
    BodyCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : Cell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;

private:
    texture::PrimaryCell texture;
};


#endif //ECOSYSTEM_BODYCELL_H
