//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BCELL_H
#define ECOSYSTEM_BCELL_H


#include "cell.h"
#include "../textures/brainCell.h"

class BCell : public Cell {
public:
    BCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : Cell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;

private:
    texture::BrainCell texture;
};


#endif //ECOSYSTEM_NEUTROCELL_H
