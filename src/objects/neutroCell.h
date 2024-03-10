//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

class NeutroCell : public Cell {
public:
    NeutroCell(texture::AnimationParameters animation, float radius, int size, float speed,
               sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    int type() const override { return CellType::NEUTRO; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    void update(Field &field, sf::Time deltaTime) override;
};

#endif //ECOSYSTEM_NEUTROCELL_H
