//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "cell.h"
#include "../textures/neutrophil.h"

class NeutroCell : public Cell {
public:
    NeutroCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : Cell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;

private:
    texture::Neutrophil texture;
};


#endif //ECOSYSTEM_NEUTROCELL_H
