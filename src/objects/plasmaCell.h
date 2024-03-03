//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_PLASMACELL_H
#define ECOSYSTEM_PLASMACELL_H


#include "cell.h"
#include "../textures/plasma.h"

class PlasmaCell : public Cell {
public:
    PlasmaCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : Cell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;

private:
    texture::Plasma texture;
};


#endif //ECOSYSTEM_NEUTROCELL_H
