//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"
#include "../textures/cellTexture.h"

class BodyCell : public Cell {
public:
    BodyCell(texture::AnimationParameters animation, float radius, int size, float speed,
             sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    void drawTexture(sf::RenderWindow &window) override;
};


#endif //ECOSYSTEM_BODYCELL_H
