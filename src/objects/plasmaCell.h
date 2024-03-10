//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_PLASMACELL_H
#define ECOSYSTEM_PLASMACELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

class PlasmaCell : public Cell {
public:
    PlasmaCell(texture::AnimationParameters animation, float radius, int size, float speed,
               sf::Vector2f center, sf::Color color);

    int type() const override { return CellType::PLASMA; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    void update(Field &field, sf::Time deltaTime) override { };
};


#endif //ECOSYSTEM_NEUTROCELL_H
